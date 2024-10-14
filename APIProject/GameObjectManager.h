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
	void AddGameObject()
	{
		GameObject* gameObject = new T;
		gameObject->Init();
		mPendingQueue.push_back(gameObject);
	}

	void RemoveGameObject(GameObject* gameObject)
	{
		mGameObjects.erase(std::remove(mGameObjects.begin(), mGameObjects.end(), gameObject), mGameObjects.end());
		mDestroyQueue.push_back(gameObject);
	}

	void DestroyQueue()
	{
		for (auto& gameObject : mDestroyQueue)
		{
			delete gameObject;
		}
		mDestroyQueue.clear();
	}

	void ActivePending()
	{
		for (auto& gameObject : mPendingQueue)
		{
			mGameObjects.push_back(gameObject);
		}
		mPendingQueue.clear();
	}

private:
	void release()
	{
		for (auto& gameObject : mGameObjects)
		{
			delete gameObject;
		}

		for (auto& gameObject : mDestroyQueue)
		{
			delete gameObject;
		}

		for (auto& gameObject : mPendingQueue)
		{
			delete gameObject;
		}
	}

private:
	GameObjectList mGameObjects;
	GameObjectList mPendingQueue;
	GameObjectList mDestroyQueue;
};

