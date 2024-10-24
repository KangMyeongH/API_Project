#include "pch.h"
#include "SpriteRenderer.h"

#include "RenderManager.h"

SpriteRenderer::SpriteRenderer(GameObject* owner, int layer) : Renderer(owner,layer), mImage(nullptr),
                                                               mTargetRect({0, 0, 0, 0}),
                                                               mRenderRect({0, 0, 0, 0}), mParallaxFactor({1.f, 1.f}),
                                                               mAngle(0),
                                                               mOpacity(1.0f), mWidth(0),
                                                               mHeight(0), mScale(1.f),
                                                               mFrame(0),
                                                               mFlip(false),
                                                               mPivotDown(false)
{
	mTransform = owner->GetTransform();
}

/*
SpriteRenderer::SpriteRenderer(GameObject* owner, HDC hdc, float width, float height, int layer)
	: Behaviour(owner), mTransform(nullptr), mDC(hdc), mWidth(width), mHeight(height), mFrame(0), mFlip(false),
	  mLayer(layer)
{
	mTransform = owner->GetTransform();
}*/

SpriteRenderer::SpriteRenderer(GameObject* owner, ID2D1Bitmap* image, float width, float height, int layer)
	: Renderer(owner, layer), mTransform(nullptr), mImage(image),
	  mTargetRect({0, 0, 0, 0}),
	  mRenderRect({0, 0, 0, 0}), mParallaxFactor({1.f,1.f}), mAngle(0),
	  mOpacity(1.0f),
	  mWidth(width),
	  mHeight(height), mScale(1.f),
	  mFrame(0),
		mFlip(false), mPivotDown(false)
{
	mTransform = owner->GetTransform();
}

/*
void SpriteRenderer::ChangeSprite(HDC hdc, float width, float height, int startFrame)
{
	mDC = hdc;
	mWidth = width;
	mHeight = height;
	mFrame = startFrame;
}*/

void SpriteRenderer::ChangeSprite(ID2D1Bitmap* image, float width, float height, int startFrame)
{
	mImage = image;
	mWidth = width;
	mHeight = height;
	mFrame = startFrame;
}

void SpriteRenderer::SetFrame(int frame)
{
	if (!mPivotDown)
	{
		mRenderRect = RectF(
			mTransform->GetWorldPosition().x - (mWidth * 0.5f),
			mTransform->GetWorldPosition().y - (mHeight * 0.5f),
			mTransform->GetWorldPosition().x + (mWidth * 0.5f),
			mTransform->GetWorldPosition().y + (mHeight * 0.5f)
		);
	}

	else if (mPivotDown)
	{
		mRenderRect = RectF(
			mTransform->GetWorldPosition().x - (mWidth * 0.5f),
			mTransform->GetWorldPosition().y - mHeight,
			mTransform->GetWorldPosition().x + (mWidth * 0.5f),
			mTransform->GetWorldPosition().y
		);
	}

	mTargetRect = RectF(
		mWidth * static_cast<float>(frame), 
		mHeight * static_cast<float>(mFlip),
		mWidth * static_cast<float>(frame + 1), 
		mHeight * static_cast<float>(mFlip + 1)
	);

	mFrame = frame;
}

void SpriteRenderer::Destroy()
{
	RenderManager::GetInstance().RemoveRenderer(this);
}
