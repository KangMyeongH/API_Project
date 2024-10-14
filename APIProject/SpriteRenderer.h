#pragma once
#include "Behaviour.h"
#include "GameObject.h"

class SpriteRenderer : public Behaviour
{
public:
	explicit SpriteRenderer(GameObject* owner) : Behaviour(owner), mDC(nullptr), mWidth(0), mHeight(0) {}
	SpriteRenderer(GameObject* owner, HDC hdc, int width, int height) : Behaviour(owner), mDC(hdc), mWidth(width), mHeight(height) {}

	void Render(HDC hdc, int x, int y) const
	{
		GdiTransparentBlt(hdc,
			x, y,
			mWidth, mHeight,
			mDC,
			0, 0,
			mWidth, mHeight,
			RGB(0, 0, 0));
	}

private:
	HDC mDC;
	int mWidth;
	int mHeight;
};

