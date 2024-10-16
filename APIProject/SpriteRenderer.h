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
		render->DrawBitmap(
			mImage,
			mRenderRect,	// ȭ�鿡 �׷��� ��ǥ ����
			mOpacity,			// ����
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // ���� ���
			mTargetRect		// ���� ��������Ʈ ��Ʈ�� Ư�� ����
		);
	}

	//void 	ChangeSprite(HDC hdc, float width, float height, int startFrame);

	void 	ChangeSprite(ID2D1Bitmap* image, float width, float height, int startFrame);

	void 	SetFrame(int frame);

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
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	int				mFrame;
	int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

