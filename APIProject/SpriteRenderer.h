#pragma once
#include "Behaviour.h"
#include "GameObject.h"

class SpriteRenderer : public Behaviour
{
public:
	explicit SpriteRenderer(GameObject* owner);
	SpriteRenderer(GameObject* owner, HDC hdc, float width, float height, int layer);

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
	}

	void ChangeSprite(HDC hdc, float width, float height, int startFrame);

	void SetFrame(int frame) { mFrame = frame; }

	void Flip(bool flip) { mFlip = flip; }

	void Destroy() override;

private:
	Transform* 	mTransform;
	HDC 		mDC;
	float 		mWidth;
	float 		mHeight;
	int			mFrame;
	bool		mFlip;
	int			mLayer;
};

