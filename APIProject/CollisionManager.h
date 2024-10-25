#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Collider.h"
class Rigidbody;
class Collider;

class CollisionManager
{
private:
	CollisionManager() = default;
	~CollisionManager();
public:
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	CollisionManager& operator=(CollisionManager&&) = delete;

public:
	static CollisionManager& GetInstance() { static CollisionManager sMgr; return sMgr; }

	// 대기 상태인 컴포넌트를 업데이트할 수 있게 collider vector에 올려주는 함수
	void RegisterForUpdate();

	// 삭제 대기 상태인 컴포넌트(Collider)들을 지워주는 함수
	void ClearDestroyColliderQueue();

	void AddCollider(Collider* collider)
	{
		mPendingColliderQueue.push_back(collider);
	}

	void RemoveCollider(Collider* collider)
	{
		mDestroyColliderQueue.push_back(collider);
	}

	void CheckCollisions();

	std::vector<Collider*>* GetColliders() { return &mColliders; }

	static CollisionDirection DetectBoxCollisionDir(RECT objRect, RECT otherRect);
	static CollisionDirection DetectEdgeCollisionDir(Rigidbody* obj, RECT other);
	static void AdjustRect(Collider* collider, Collider* other, CollisionDirection dir);

	void Debug(ID2D1DeviceContext* render);

	void Release();
	

private:
	// 둘 중 하나라도 rigidbody가 있어야지 collisionXXX 판정이 되므로 Collision 여부 판단
	//bool CanCollide(const Collider* colliderA, const Collider* colliderB);

private:
	std::vector<Collider*>	mColliders;
	std::list<Collider*>	mPendingColliderQueue;
	std::list<Collider*>	mDestroyColliderQueue;

	std::unordered_map<Collider*, std::unordered_set<Collider*>> mCollisionMap;
};

