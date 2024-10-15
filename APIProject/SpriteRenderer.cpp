#include "pch.h"
#include "SpriteRenderer.h"

#include "RenderManager.h"

SpriteRenderer::SpriteRenderer(GameObject* owner) : Behaviour(owner), mTransform(nullptr), mDC(nullptr), mWidth(0),
                                                    mHeight(0), mFrame(0), mFlip(false), mLayer(0)
{
	mTransform = owner->GetTransform();
}

SpriteRenderer::SpriteRenderer(GameObject* owner, HDC hdc, float width, float height, int layer)
	: Behaviour(owner), mTransform(nullptr), mDC(hdc), mWidth(width), mHeight(height), mFrame(0), mFlip(false),
	  mLayer(layer)
{
	mTransform = owner->GetTransform();
}

void SpriteRenderer::ChangeSprite(HDC hdc, float width, float height, int startFrame)
{
	mDC = hdc;
	mWidth = width;
	mHeight = height;
	mFrame = startFrame;
}

void SpriteRenderer::Destroy()
{
	RenderManager::GetInstance().RemoveSprite(this);
	mOwner->RemoveComponent(this);
}
