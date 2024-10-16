#include "pch.h"
#include "RenderManager.h"

#include "SpriteRenderer.h"

RenderManager::~RenderManager()
{
	for (auto& sprite : mSprites)
	{
		delete sprite;
	}

	for (auto& sprite : mPendingSpriteQueue)
	{
		delete sprite;
	}
}

void RenderManager::RegisterForUpdate()
{
	for (auto it = mPendingSpriteQueue.begin(); it != mPendingSpriteQueue.end();)
	{
		SpriteRenderer* sprite = *it;

		if (sprite->IsEnabled())
		{
			mSprites.push_back(sprite);
			mLayerMultiMap.insert({ sprite->GetLayer(),sprite });
			it = mPendingSpriteQueue.erase(it);
		}

		else ++it;
	}

}

void RenderManager::ClearDestroyColliderQueue()
{
	for (auto& sprite : mDestroySpriteQueue)
	{
		delete sprite;
		mSprites.erase(std::remove(mSprites.begin(), mSprites.end(), sprite), mSprites.end());
		for (auto it = mLayerMultiMap.begin(); it != mLayerMultiMap.end();)
		{
			if (it->second == sprite)
			{
				it = mLayerMultiMap.erase(it);
			}

			else ++it;
		}
	}

	mDestroySpriteQueue.clear();
}

void RenderManager::AddSprite(SpriteRenderer* sprite)
{
	mPendingSpriteQueue.push_back(sprite);
}

void RenderManager::RemoveSprite(SpriteRenderer* sprite)
{
	mDestroySpriteQueue.push_back(sprite);
}

/*
void RenderManager::Rendering(HDC hdc) const
{
	for (auto& sprite : mLayerMultiMap)
	{
		sprite.second->Render(hdc);
	}
}*/

void RenderManager::Rendering(ID2D1HwndRenderTarget* render) const
{
	for (auto& sprite : mLayerMultiMap)
	{
		if (sprite.second->IsEnabled())
		{
			sprite.second->Render(render);
		}
	}
}
