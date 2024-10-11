#pragma once
#include <vector>

#include "MonoBehaviour.h"

class MonoBehaviourManager
{
private:
	MonoBehaviourManager() = default;
	~MonoBehaviourManager();
public:
	MonoBehaviourManager(const MonoBehaviourManager&) = delete;
	MonoBehaviourManager(MonoBehaviourManager&&) = delete;
	MonoBehaviourManager& operator=(const MonoBehaviourManager&) = delete;
	MonoBehaviourManager& operator=(MonoBehaviourManager&&) = delete;

public:
	static MonoBehaviourManager& GetInstance() { static MonoBehaviourManager sMgr; return sMgr; }

public:
	void Start()
	{
		for (auto it = mPendingQueue.begin(); it != mPendingQueue.end();)
		{
			MonoBehaviour* monoBehaviour = *it;

			if (monoBehaviour->IsEnabled())
			{
				monoBehaviour->OnEnable();
				monoBehaviour->Start();
				registerForUpdates(monoBehaviour);

				it = mPendingQueue.erase(it);
			}

			else ++it;
		}
	}

	void FixedUpdate()
	{
		for (auto& monoBehaviour : mFixedUpdateMonoBehaviours)
		{
			if (monoBehaviour->IsEnabled())
			{
				monoBehaviour->FixedUpdate();
			}
		}
	}

	void Update()
	{
		for	(auto& monoBehaviour : mUpdateMonoBehaviours)
		{
			if (monoBehaviour->IsEnabled())
			{
				monoBehaviour->Update();
			}
		}
	}

	void LateUpdate()
	{
		for (auto& monoBehaviour : mLateUpdateMonoBehaviours)
		{
			if (monoBehaviour->IsEnabled())
			{
				monoBehaviour->LateUpdate();
			}
		}
	}

	void OnDestroy()
	{
		for (auto& obj : mDestroyQueue)
		{
			obj->OnDestroy();
			unregisterFromUpdates(obj);
		}

		mDestroyQueue.clear();
	}

	void AddMonoBehaviour(MonoBehaviour* monoBehaviour)
	{
		mPendingQueue.push_back(monoBehaviour);
		monoBehaviour->Awake();
	}

	void RemoveBehaviour(MonoBehaviour* monoBehaviour)
	{
		mDestroyQueue.push_back(monoBehaviour);
		mMonoBehaviours.erase(std::remove(mMonoBehaviours.begin(), mMonoBehaviours.end(), monoBehaviour), mMonoBehaviours.end());
	}

	void ClearDestroyQueue()
	{
		for (auto& obj : mDestroyQueue)
		{
			delete obj;
		}

		mDestroyQueue.clear();
	}

private:
	void registerForUpdates(MonoBehaviour* obj)
	{
		if (obj->GetUpdateType() & UPDATE) mUpdateMonoBehaviours.push_back(obj);
		if (obj->GetUpdateType() & FIXED_UPDATE) mFixedUpdateMonoBehaviours.push_back(obj);
		if (obj->GetUpdateType() & LATE_UPDATE) mLateUpdateMonoBehaviours.push_back(obj);
	}

	void unregisterFromUpdates(MonoBehaviour* obj)
	{
		eraseFromVector(mUpdateMonoBehaviours, obj);
		eraseFromVector(mFixedUpdateMonoBehaviours, obj);
		eraseFromVector(mLateUpdateMonoBehaviours, obj);
	}

	void eraseFromVector(std::vector<MonoBehaviour*>& vec, MonoBehaviour* obj)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());
	}

private:
	std::vector<MonoBehaviour*> 	mMonoBehaviours;
	std::list<MonoBehaviour*> 		mPendingQueue;
	std::vector<MonoBehaviour*> 	mUpdateMonoBehaviours;
	std::vector<MonoBehaviour*> 	mFixedUpdateMonoBehaviours;
	std::vector<MonoBehaviour*> 	mLateUpdateMonoBehaviours;
	std::list<MonoBehaviour*>		mDestroyQueue;
};