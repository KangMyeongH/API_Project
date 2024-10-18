#pragma once
#include "Behaviour.h"
#include "GameObject.h"

// �Ű� ������ hdc, width, height, layer�� �޴´�
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
		// ȸ�� �߽� (mRenderRect�� �߽��� �������� ȸ���Ѵٰ� ����)
		D2D1_POINT_2F center = D2D1::Point2F(
			(mRenderRect.left + mRenderRect.right) / 2.0f,
			(mRenderRect.top + mRenderRect.bottom) / 2.0f
		);

		// ���� ��ȯ ���� ����
		D2D1_MATRIX_3X2_F oldTransform;
		render->GetTransform(&oldTransform);

		// ȸ�� ��ȯ ����
		render->SetTransform(D2D1::Matrix3x2F::Rotation(mAngle, center));

		render->DrawBitmap(
			mImage,
			mRenderRect,	// ȭ�鿡 �׷��� ��ǥ ����
			mOpacity,			// ����
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // ���� ���
			mTargetRect		// ���� ��������Ʈ ��Ʈ�� Ư�� ����
		);

		// ���� ��ȯ ���� ����
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
	D2D1_RECT_F		mTargetRect;	// ��������Ʈ ��Ʈ�� Ư�� ����
	D2D1_RECT_F		mRenderRect;	// ȭ���� �׷��� ��ġ
	float			mAngle;
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	int				mFrame;
	int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

