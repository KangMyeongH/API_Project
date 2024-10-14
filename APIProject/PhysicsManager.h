#pragma once
#include <vector>

#include "Rigidbody.h"

class PhysicsManager
{
private:
	PhysicsManager() = default;
	~PhysicsManager();
public:
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager(PhysicsManager&&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
	PhysicsManager& operator=(PhysicsManager&&) = delete;

public:
	static PhysicsManager& GetInstance() { static PhysicsManager sMgr; return sMgr; }

public:
	// 대기 상태인 컴포넌트를 업데이트할 수 있게 vector에 올려주는 함수
	void RegisterForUpdate();

	// 게임 루프에 들어갈 update
	void RigidbodyUpdate(float deltaTime) const;

	void AddRigidbody(Rigidbody* rigidbody)
	{
		mPendingRigidbodyQueue.push_back(rigidbody);
	}

	void RemoveRigidbody(Rigidbody* rigidbody)
	{
		mDestroyRigidbodyQueue.push_back(rigidbody);
	}

	void ClearDestroyRigidbodyQueue()
	{
		for (auto& obj : mDestroyRigidbodyQueue)
		{
			delete obj;
			unregisterFromRigidbodyUpdates(obj);
		}

		mDestroyRigidbodyQueue.clear();
	}

private:
	void registerForRigidbodyUpdate(Rigidbody* rigidbody)
	{
		mRigidbodies.push_back(rigidbody);
	}

	void unregisterFromRigidbodyUpdates(Rigidbody* obj)
	{
		eraseFromRigidbodyVector(mRigidbodies, obj);
	}

	void eraseFromRigidbodyVector(std::vector<Rigidbody*>& vec, Rigidbody* obj)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());
	}

private:
	std::vector<Rigidbody*> 	mRigidbodies;
	std::list<Rigidbody*>		mPendingRigidbodyQueue;
	std::list<Rigidbody*>		mDestroyRigidbodyQueue;
};

