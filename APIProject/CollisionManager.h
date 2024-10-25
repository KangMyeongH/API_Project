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

	// ��� ������ ������Ʈ�� ������Ʈ�� �� �ְ� collider vector�� �÷��ִ� �Լ�
	void RegisterForUpdate();

	// ���� ��� ������ ������Ʈ(Collider)���� �����ִ� �Լ�
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
	// �� �� �ϳ��� rigidbody�� �־���� collisionXXX ������ �ǹǷ� Collision ���� �Ǵ�
	//bool CanCollide(const Collider* colliderA, const Collider* colliderB);

private:
	std::vector<Collider*>	mColliders;
	std::list<Collider*>	mPendingColliderQueue;
	std::list<Collider*>	mDestroyColliderQueue;

	std::unordered_map<Collider*, std::unordered_set<Collider*>> mCollisionMap;
};

