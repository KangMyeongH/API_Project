#include "pch.h"
#include "MonoBehaviourManager.h"

#include "GameObjectManager.h"

MonoBehaviourManager::~MonoBehaviourManager()
{
	for (auto& mb : mMonoBehaviours)
	{
		delete mb;
	}

	for (auto& mb :mPendingQueue)
	{
		delete mb;
	}

	for (auto& mb : mDestroyQueue)
	{
		delete mb;
	}
}

void MonoBehaviourManager::ClearDestroyQueue()
{
	for (auto& obj : mDestroyQueue)
	{
		GameObjectList* objList = GameObjectManager::GetInstance().GetGameObjectList();
		for (int i = 0; i < END_TAG; ++i)
		{
			for (auto& go : objList[i])
			{
				if (go == obj->GetGameObject())
				{
					obj->GetGameObject()->RemoveComponent(obj);
					i = END_TAG;
					break;
				}
			}
		}

		delete obj;
		mMonoBehaviours.erase(std::remove(mMonoBehaviours.begin(), mMonoBehaviours.end(), obj), mMonoBehaviours.end());
	}

	mDestroyQueue.clear();
}
