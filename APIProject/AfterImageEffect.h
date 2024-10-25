#pragma once
#include "Camera.h"
#include "Renderer.h"
class AfterImageEffect : public Renderer
{
public:
	AfterImageEffect(GameObject* owner, int layer)
		: Renderer(owner, layer), mImage(nullptr), mTargetRect(), mRenderRect(), mOpacity(1.f), mAngle(0), mScale(0),
		  mFlip(false) {}

	void Render(ID2D1DeviceContext* render) override
	{
		D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(mRenderRect);

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

		// ColorMatrix
		ID2D1Effect* colorEffect = nullptr;
		//render->CreateEffect()

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

	void SetInfo(ID2D1Bitmap* image, D2D1_RECT_F targetRect, D2D1_RECT_F renderRect, float angle, float scale, bool flip)
	{
		mImage = image;
		mTargetRect = targetRect;
		mRenderRect = renderRect;
		mAngle = angle;
		mScale = scale;
		mFlip = flip;
	}

private:
	ID2D1Bitmap* 	mImage;
	D2D1_RECT_F		mTargetRect;
	D2D1_RECT_F		mRenderRect;
	float			mOpacity;
	float			mAngle;
	float			mScale;
	bool			mFlip;
};

