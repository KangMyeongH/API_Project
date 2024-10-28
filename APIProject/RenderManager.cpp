#include "pch.h"
#include "RenderManager.h"

#include "GameObjectManager.h"
#include "SpriteRenderer.h"

RenderManager::~RenderManager()
{
	for (auto& sprite : mRenders)
	{
		delete sprite;
	}

	for (auto& sprite : mPendingRenderQueue)
	{
		delete sprite;
	}
}

void RenderManager::RegisterForUpdate()
{
	for (auto it = mPendingRenderQueue.begin(); it != mPendingRenderQueue.end();)
	{
		Renderer* sprite = *it;

		if (sprite->IsEnabled())
		{
			mRenders.push_back(sprite);
			mLayerMultiMap.insert({ sprite->GetLayer(),sprite });
			it = mPendingRenderQueue.erase(it);
		}

		else ++it;
	}

}

void RenderManager::ClearDestroyColliderQueue()
{
	for (auto& sprite : mDestroyRenderQueue)
	{
		GameObjectList* objList = GameObjectManager::GetInstance().GetGameObjectList();
		for (int i = 0; i < END_TAG; ++i)
		{
			for (auto& go : objList[i])
			{
				if (go == sprite->GetGameObject())
				{
					sprite->GetGameObject()->RemoveComponent(sprite);
					i = END_TAG;
					break;
				}
			}
		}

		delete sprite;

		mRenders.erase(std::remove(mRenders.begin(), mRenders.end(), sprite), mRenders.end());
		for (auto it = mLayerMultiMap.begin(); it != mLayerMultiMap.end();)
		{
			if (it->second == sprite)
			{
				it = mLayerMultiMap.erase(it);
			}

			else ++it;
		}
	}

	mDestroyRenderQueue.clear();
}

void RenderManager::AddRenderer(Renderer* sprite)
{
	mPendingRenderQueue.push_back(sprite);
}

void RenderManager::RemoveRenderer(Renderer* sprite)
{
	for (auto& sp : mDestroyRenderQueue)
	{
		if (sp == sprite)
		{
			return;
		}
	}
	mDestroyRenderQueue.push_back(sprite);
}

/*
void RenderManager::Rendering(HDC hdc) const
{
	for (auto& sprite : mLayerMultiMap)
	{
		sprite.second->Render(hdc);
	}
}*/

void RenderManager::Rendering(ID2D1DeviceContext* render) const
{
	for (auto& sprite : mLayerMultiMap)
	{
		if (sprite.second->IsEnabled())
		{
			sprite.second->Render(render);
		}
	}
}

void RenderManager::Release()
{
	for (auto& sprite : mRenders)
	{
		delete sprite;
	}

	for (auto& sprite : mPendingRenderQueue)
	{
		delete sprite;
	}

	mRenders.clear();
	mPendingRenderQueue.clear();
	mLayerMultiMap.clear();
}
