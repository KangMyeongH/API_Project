#pragma once
#include "Transform.h"

// y 132
class Camera
{
private:
	Camera(float x, float y, float width, float height, float zoom = 1.f)
		: mTarget(nullptr), mBoundary({0, 0, WIN_WIDTH, WIN_HEIGHT}), mPosition({x, y}), mOriginalWidth(width),
		  mOriginalHeight(height),
		  mWidth(width), mHeight(height), mZoom(zoom),
		  mShakeDuration(0),
		  mShakeAmplitude(0)
	{
	}

	~Camera() = default;
public:
	Camera(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera& operator=(Camera&&) = delete;

public:
	static Camera& GetInstance() { static Camera sMgr(960, 540, WIN_WIDTH, WIN_HEIGHT); return sMgr; }

	void SetTarget(Transform* target) { mTarget = target; }
	void DetachTarget() { mTarget = nullptr; }

	void SetOffset(const Vector2& offset)
	{
		mOriginalOffset = offset;
		mOffset = offset / mZoom;
	}

	void SetPosition(float x, float y)
	{
		// 카메라의 좌상단(LeftTop)과 우하단(RightBottom) 좌표 계산
		float halfWidth = mWidth / 2.0f;
		float halfHeight = mHeight / 2.0f;

		// 좌상단이 경계를 벗어나지 않도록 제한
		float clampedLeft = Clamp(x - halfWidth, mBoundary.left, mBoundary.right - mWidth);
		float clampedTop = Clamp(y - halfHeight, mBoundary.top, mBoundary.bottom - mHeight);

		// 카메라의 중심 좌표를 재설정 (사각형 중심이 경계 내에 있도록)
		mPosition.x = clampedLeft + halfWidth;
		mPosition.y = clampedTop + halfHeight;
	}
	D2D1_POINT_2F GetPosition() const { return mPosition; }

	void SetBoundary(float left, float top, float right, float bottom)
	{
		mBoundary = { left,top,right,bottom };
	}

	void SetZoom(float zoom)
	{
		mZoom = zoom;

		mOffset = mOriginalOffset / mZoom;
		mWidth = mOriginalWidth / mZoom;
		mHeight = mOriginalHeight / mZoom;
	}
	float GetZoom() const { return mZoom; }

	float GetWidth() const { return mWidth; }

	D2D1_RECT_F GetBoundary() const { return mBoundary; }

	void Move(float dx, float dy) { mPosition.x += dx; mPosition.y += dy; }

	// 월드 좌표를 스크린 좌표로 변환
	D2D1_RECT_F WorldToScreen(const D2D1_RECT_F& worldRect) const
	{
		D2D1_RECT_F screenRect;

		// 흔들림 오프셋 적용 (카메라가 흔들리는 경우)
		float shakeOffsetX = mShakeAmplitude * (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f;
		float shakeOffsetY = mShakeAmplitude * (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f;

		// 카메라의 중심을 기준으로 월드 좌표를 화면 좌표로 변환
		float halfWidth = mWidth * 0.5f;
		float halfHeight = mHeight * 0.5f;

		// 카메라 중심으로부터의 상대적인 위치 계산 (화면 변환)
		screenRect.left = (worldRect.left - (mPosition.x - halfWidth + shakeOffsetX)) * mZoom;
		screenRect.top = (worldRect.top - (mPosition.y - halfHeight + shakeOffsetY)) * mZoom;
		screenRect.right = (worldRect.right - (mPosition.x - halfWidth + shakeOffsetX)) * mZoom;
		screenRect.bottom = (worldRect.bottom - (mPosition.y - halfHeight + shakeOffsetY)) * mZoom;

		return screenRect;
	}

	D2D1_POINT_2F WorldToScreenVector(const D2D1_POINT_2F& worldPosition) const
	{
		D2D1_POINT_2F screenPosition;

		// 카메라 위치에 흔들림 오프셋 적용
		float shakeOffsetX = mShakeAmplitude * (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f;
		float shakeOffsetY = mShakeAmplitude * (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f;

		float halfWidth = mWidth * 0.5f;
		float halfHeight = mHeight * 0.5f;

		screenPosition.x = (worldPosition.x - (mPosition.x - halfWidth + shakeOffsetX)) * mZoom;
		screenPosition.y = (worldPosition.y - (mPosition.y - halfHeight + shakeOffsetY)) * mZoom;

		return screenPosition;
	}

	Vector2 WorldToScreenMouse(const Vector2& mousePos) const
	{
		Vector2 screenPosition;
		screenPosition.x = (mousePos.x / mZoom) + (mPosition.x - (mWidth * 0.5f));
		screenPosition.y = (mousePos.y / mZoom) + (mPosition.y - (mHeight * 0.5f));

		return screenPosition;
	}

	// 스크린 좌표를 월드 좌표로 변환
	D2D1_RECT_F ScreenToWorld(const D2D1_RECT_F& screenRect) const
	{
		D2D1_RECT_F worldRect;
		worldRect.left = screenRect.left / mZoom + mPosition.x;
		worldRect.top = screenRect.top / mZoom + mPosition.y;
		worldRect.right = screenRect.right / mZoom + mPosition.x;
		worldRect.bottom = screenRect.bottom / mZoom + mPosition.y;
		return worldRect;
	}

	// duration = 지속 시간, amplitude = 강도
	void Shake(float duration, float amplitude)
	{
		mShakeDuration = duration;
		mShakeAmplitude = amplitude;
	}

	void Update(float deltaTime)
	{
		if (mTarget)
		{
			SetPosition(mTarget->GetWorldPosition().x + mOffset.x, mTarget->GetWorldPosition().y + mOffset.y);
		}

		if (mShakeDuration > 0)
		{
			// 흔들림 지속 시간 감소
			mShakeDuration -= deltaTime;

			// 흔들림이 끝나면 진폭을 0으로 설정
			if (mShakeDuration <= 0)
			{
				mShakeAmplitude = 0;
				mShakeDuration = 0;
			}
		}
	}

private:
	// 값이 범위를 벗어나지 않도록 클램프(제한)하는 함수
	float Clamp(float value, float min, float max) const
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

private:
	Transform* mTarget;
	Vector2 mOriginalOffset;
	Vector2 mOffset;
	D2D1_RECT_F mBoundary;
	D2D1_POINT_2F mPosition;
	float mOriginalWidth;
	float mOriginalHeight;
	float mWidth;
	float mHeight;
	float mZoom;
	float mShakeDuration;	// 흔들림 지속 시간
	float mShakeAmplitude;  // 흔들림 진폭
};
