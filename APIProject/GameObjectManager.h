#pragma once
#include "GameObject.h"

class GameObjectManager
{
private:
	GameObjectManager() {}
	~GameObjectManager() { Release(); }

public:
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;

public:
	static GameObjectManager& GetInstance() { static GameObjectManager sMgr; return sMgr; }

	template<typename T>
	GameObject* AddGameObject()
	{
		GameObject* gameObject = new T;
		gameObject->Init();
		mPendingQueue.push_back(gameObject);

		return gameObject;
	}

	void RemoveGameObject(GameObject* gameObject)
	{
		for (auto& obj : mDestroyQueue)
		{
			if (obj == gameObject)
			{
				return;
			}
		}
		mDestroyQueue.push_back(gameObject);
	}

	GameObjectList* GetGameObjectList()
	{
		return mGameObjects;
	}

	GameObjectList* GetGameObjectsForTag(Tag tag)
	{
		return &mGameObjects[tag];
	}

	void DestroyQueue()
	{
		for (auto& gameObject : mDestroyQueue)
		{
			mGameObjects[gameObject->GetTag()].erase(std::remove(mGameObjects[gameObject->GetTag()].begin(), mGameObjects[gameObject->GetTag()].end(), gameObject), mGameObjects[gameObject->GetTag()].end());
			delete gameObject;
		}
		mDestroyQueue.clear();
	}

	void ActivePending()
	{
		for (auto& gameObject : mPendingQueue)
		{
			mGameObjects[gameObject->GetTag()].push_back(gameObject);
		}
		mPendingQueue.clear();
	}

	void Release()
	{
		for (auto& mGameObject : mGameObjects)
		{
			for (auto& gameObject : mGameObject)
			{
				delete gameObject;
			}
		}

		for (auto& gameObject : mPendingQueue)
		{
			delete gameObject;
		}

		mGameObjects->clear();
		mPendingQueue.clear();
	}

private:
	GameObjectList mGameObjects[END_TAG];
	GameObjectList mPendingQueue;
	GameObjectList mDestroyQueue;
};

