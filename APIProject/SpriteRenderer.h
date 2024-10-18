#pragma once
#include "Behaviour.h"
#include "GameObject.h"

// 매게 변수로 hdc, width, height, layer를 받는다
class SpriteRenderer : public Behaviour
{
public:
	explicit SpriteRenderer(GameObject* owner, int layer);
	//SpriteRenderer(GameObject* owner, HDC hdc, float width, float height, int layer);
	SpriteRenderer(GameObject* owner, ID2D1Bitmap* image, float width, float height, int layer);

	/*
	void Render(HDC hdc) const
	{
		GdiTransparentBlt(hdc,
			static_cast<int>(mTransform->GetWorldPosition().x - (mWidth * 0.5f)),
			static_cast<int>(mTransform->GetWorldPosition().y - (mHeight * 0.5f)),
			static_cast<int>(mWidth),
			static_cast<int>(mHeight),
			mDC,
			static_cast<int>(mWidth) * mFrame, 
			static_cast<int>(mHeight) * mFlip,
			static_cast<int>(mWidth),
			static_cast<int>(mHeight),
			RGB(0, 0, 0));
	}*/

	void Render(ID2D1HwndRenderTarget* render) const
	{
		// 회전 중심 (mRenderRect의 중심을 기준으로 회전한다고 가정)
		D2D1_POINT_2F center = D2D1::Point2F(
			(mRenderRect.left + mRenderRect.right) / 2.0f,
			(mRenderRect.top + mRenderRect.bottom) / 2.0f
		);

		// 현재 변환 상태 저장
		D2D1_MATRIX_3X2_F oldTransform;
		render->GetTransform(&oldTransform);

		// 회전 변환 적용
		render->SetTransform(D2D1::Matrix3x2F::Rotation(mAngle, center));

		render->DrawBitmap(
			mImage,
			mRenderRect,	// 화면에 그려질 목표 영역
			mOpacity,			// 투명도
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // 보간 모드
			mTargetRect		// 원본 스프라이트 시트의 특정 영역
		);

		// 원래 변환 상태 복원
		render->SetTransform(oldTransform);
	}

	//void 	ChangeSprite(HDC hdc, float width, float height, int startFrame);

	void 	ChangeSprite(ID2D1Bitmap* image, float width, float height, int startFrame);

	void 	SetFrame(int frame);

	void	SetAngle(float angle) { mAngle = angle; }

	int		GetLayer() const { return mLayer; }

	void 	Flip(bool flip) { mFlip = flip; }

	void 	Destroy() override;

	void	IsPivotDown(const bool down) { mPivotDown = down; }

private:
	Transform* 		mTransform;
	//HDC 			mDC;
	ID2D1Bitmap* 	mImage;
	D2D1_RECT_F		mTargetRect;	// 스프라이트 시트의 특정 영역
	D2D1_RECT_F		mRenderRect;	// 화면의 그려줄 위치
	float			mAngle;
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	int				mFrame;
	int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

