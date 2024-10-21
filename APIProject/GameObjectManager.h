#pragma once
#include "GameObject.h"

class GameObjectManager
{
private:
	GameObjectManager() {}
	~GameObjectManager() { release(); }

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
		mDestroyQueue.push_back(gameObject);
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

private:
	void release()
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
	}

private:
	GameObjectList mGameObjects[END_TAG];
	GameObjectList mPendingQueue;
	GameObjectList mDestroyQueue;
};

