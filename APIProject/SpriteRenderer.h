#pragma once
#include "Behaviour.h"
#include "Camera.h"
#include "GameObject.h"

// 매게 변수로 hdc, width, height, layer를 받는다
class SpriteRenderer : public Behaviour
{
public:
	explicit SpriteRenderer(GameObject* owner, int layer);
	SpriteRenderer(GameObject* owner, ID2D1Bitmap* image, float width, float height, int layer);

	void Render(ID2D1HwndRenderTarget* render) const
	{
		D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(mRenderRect);

		/*
		// 카메라의 움직임에 따라 배경 위치를 조정
		screenRect.left += (Camera::GetInstance().GetPosition().x * mParallaxFactor.x);
		screenRect.right += (Camera::GetInstance().GetPosition().x * mParallaxFactor.x);
		screenRect.top += (Camera::GetInstance().GetPosition().y * mParallaxFactor.y);
		screenRect.bottom += (Camera::GetInstance().GetPosition().y * mParallaxFactor.y);
		*/
		// 회전 중심 (mRenderRect의 중심을 기준으로 회전한다고 가정)
		D2D1_POINT_2F center = D2D1::Point2F(
			(screenRect.left + screenRect.right) / 2.0f,
			(screenRect.top + screenRect.bottom) / 2.0f
		);

		// 현재 변환 상태 저장
		D2D1_MATRIX_3X2_F oldTransform;
		render->GetTransform(&oldTransform);

		// 스케일 변환 적용
		D2D1_MATRIX_3X2_F scaleMatrix = Matrix3x2F::Scale(mScale, mScale, center);

		// 회전 변환 적용
		D2D1_MATRIX_3X2_F rotationMatrix = Matrix3x2F::Rotation(mAngle, center);

		// 변환 적용
		render->SetTransform(scaleMatrix * rotationMatrix * oldTransform);

		render->DrawBitmap(
			mImage,
			screenRect,	// 화면에 그려질 목표 영역
			mOpacity,			// 투명도
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // 보간 모드
			mTargetRect		// 원본 스프라이트 시트의 특정 영역
		);

		// 원래 변환 상태 복원
		render->SetTransform(oldTransform);
	}

	void 	ChangeSprite(ID2D1Bitmap* image, float width, float height, int startFrame);

	void 	SetFrame(int frame);

	void	SetAngle(float angle) { mAngle = angle; }

	void	SetScale(float scale) { mScale = scale; }

	void	SetParallaxFactor(const Vector2& vel) { mParallaxFactor = vel; }

	int		GetLayer() const { return mLayer; }

	float	GetWidth() const { return mWidth; }

	void 	Flip(bool flip) { mFlip = flip; }

	void 	Destroy() override;

	void	IsPivotDown(const bool down) { mPivotDown = down; }

	ID2D1Bitmap* GetBitmap() const { return mImage; }

private:
	Transform* 		mTransform;
	ID2D1Bitmap* 	mImage;
	D2D1_RECT_F		mTargetRect;	// 스프라이트 시트의 특정 영역
	D2D1_RECT_F		mRenderRect;	// 화면의 그려줄 위치
	Vector2			mParallaxFactor; // 패럴랙스 비율, 기본값은 1.0 작으면 멀고 크면 가깝다
	float			mAngle;
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	float			mScale;
	int				mFrame;
	int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

