#include "pch.h"
#include "CollisionManager.h"

#include "Collision.h"
#include "GameObject.h"
#include "Rigidbody.h"

CollisionManager::~CollisionManager()
{
	for (auto& collider : mColliders)
	{
		delete collider;
	}

	for (auto& collider : mPendingColliderQueue)
	{
		delete collider;
	}
}

void CollisionManager::RegisterForUpdate()
{
	for (auto it = mPendingColliderQueue.begin(); it != mPendingColliderQueue.end();)
	{
		Collider* collider = *it;

		if (collider->IsEnabled())
		{
			collider->Init();
			mColliders.push_back(collider);

			it = mPendingColliderQueue.erase(it);
		}

		else ++it;
	}
}

void CollisionManager::ClearDestroyColliderQueue()
{
	for (auto& obj : mDestroyColliderQueue)
	{
		delete obj;
		mColliders.erase(std::remove(mColliders.begin(), mColliders.end(), obj), mColliders.end());

		if (mCollisionMap.find(obj) != mCollisionMap.end())
		{
			for (Collider* other : mCollisionMap[obj])
			{
				mCollisionMap[other].erase(obj);
			}

			mCollisionMap.erase(obj);
		}
	}

	mDestroyColliderQueue.clear();
}

void CollisionManager::CheckCollisions()
{
	for (size_t i = 0; i < mColliders.size(); ++i)
	{
		Collider* colliderA = mColliders[i];
		if (!colliderA->IsEnabled()) continue;

		for (size_t j = i + 1; j < mColliders.size(); ++j)
		{
			Collider* colliderB = mColliders[j];
			if (!colliderB->IsEnabled()) continue;
			/*
			if (!CanCollide(colliderA, colliderB))
			{
				continue;
			}*/

			POINT contactPoint;
			bool isColliding = colliderA->CheckCollision(colliderB, contactPoint);

			if (isColliding)
			{
				if (mCollisionMap[colliderA].find(colliderB) == mCollisionMap[colliderA].end())
				{
					mCollisionMap[colliderA].insert(colliderB);
					colliderA->GetGameObject()->OnCollisionEnter(Collision(colliderB->GetGameObject(), contactPoint));
					colliderB->GetGameObject()->OnCollisionEnter(Collision(colliderA->GetGameObject(), contactPoint));
				}

				else
				{
					colliderA->GetGameObject()->OnCollisionStay(Collision(colliderB->GetGameObject(), contactPoint));
					colliderB->GetGameObject()->OnCollisionStay(Collision(colliderA->GetGameObject(), contactPoint));
				}
			}

			else
			{
				if (mCollisionMap[colliderA].find(colliderB) != mCollisionMap[colliderA].end())
				{
					colliderA->GetGameObject()->OnCollisionExit(Collision(colliderB->GetGameObject(), contactPoint));
					colliderB->GetGameObject()->OnCollisionExit(Collision(colliderA->GetGameObject(), contactPoint));
					mCollisionMap[colliderA].erase(colliderB);
				}
			}
		}
	}
}

CollisionDirection CollisionManager::DetectBoxCollisionDir(RECT objRect, RECT otherRect)
{
	CollisionDirection collisionDir = NONE;

	int overlapLeft = objRect.right - otherRect.left;
	int overlapRight = otherRect.right - objRect.left;
	int overlapTop = objRect.bottom - otherRect.top;
	int overlapBottom = otherRect.bottom - objRect.top;

	int minOverlap = (std::min)({ overlapLeft,overlapRight,overlapTop,overlapBottom });

	// obj가 other의 왼쪽에서 충돌
	if (minOverlap == overlapLeft)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | LEFT);
	}

	// obj가 other의 오른쪽에서 충돌
	else if (minOverlap == overlapRight)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | RIGHT);
	}

	// obj가 other의 위에서 충돌
	if (minOverlap == overlapTop)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | TOP);
	}

	// obj가 other의 아래에서 충돌
	else if (minOverlap == overlapBottom)
	{
		collisionDir = static_cast<CollisionDirection>(collisionDir | BOTTOM);
	}

	return collisionDir;
}



/*
bool CollisionManager::CanCollide(const Collider* colliderA, const Collider* colliderB)
{
	GameObject* objA = colliderA->GetGameObject();
	GameObject* objB = colliderB->GetGameObject();

	return (objA->GetComponent<Rigidbody>() != nullptr || objB->GetComponent<Rigidbody>() != nullptr);
}
*/
