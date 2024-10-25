#include "pch.h"
#include "CollisionManager.h"

#include "Collision.h"
#include "GameObject.h"
#include "GameObjectManager.h"
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
					colliderA->GetGameObject()->OnCollisionEnter(Collision(colliderB->GetGameObject(), colliderB, contactPoint));
					colliderB->GetGameObject()->OnCollisionEnter(Collision(colliderA->GetGameObject(), colliderA ,contactPoint));
				}

				else
				{
					colliderA->GetGameObject()->OnCollisionStay(Collision(colliderB->GetGameObject(), colliderB, contactPoint));
					colliderB->GetGameObject()->OnCollisionStay(Collision(colliderA->GetGameObject(), colliderA, contactPoint));
				}
			}

			else
			{
				if (mCollisionMap[colliderA].find(colliderB) != mCollisionMap[colliderA].end())
				{
					colliderA->GetGameObject()->OnCollisionExit(Collision(colliderB->GetGameObject(), colliderB, contactPoint));
					colliderB->GetGameObject()->OnCollisionExit(Collision(colliderA->GetGameObject(), colliderA, contactPoint));
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

CollisionDirection CollisionManager::DetectEdgeCollisionDir(Rigidbody* obj, RECT other)
{
	CollisionDirection collisionDir = NONE;

	// 좌우 충돌 체크 (선이 수직일 때)
	if (other.left == other.right)
	{
		if (obj->GetPrevPosition().x < static_cast<float>(other.left))
		{
			collisionDir = static_cast<CollisionDirection>(collisionDir | LEFT);
		}

		else if (obj->GetPrevPosition().x > static_cast<float>(other.left))
		{
			collisionDir = static_cast<CollisionDirection>(collisionDir | RIGHT);
		}
	}

	// 상하 충돌 체크 (선이 수평일 때)
	if (other.top == other.bottom)
	{
		if (obj->GetPrevPosition().y < static_cast<float>(other.top))
		{
			collisionDir = static_cast<CollisionDirection>(collisionDir | TOP);
		}

		else if (obj->GetPrevPosition().y < static_cast<float>(other.top))
		{
			collisionDir = static_cast<CollisionDirection>(collisionDir | BOTTOM);
		}
	}

	return collisionDir;
}

void CollisionManager::AdjustRect(Collider* collider, Collider* other, CollisionDirection dir)
{
	Vector2 adjustPosition = collider->GetTransform()->GetWorldPosition();

	if (dir & LEFT)
	{
		adjustPosition.x = adjustPosition.x - static_cast<float>(collider->GetRect()->right - other->GetRect()->left);
	}
	else if (dir & RIGHT)
	{
		adjustPosition.x = adjustPosition.x + static_cast<float>(other->GetRect()->right - collider->GetRect()->left);
	}

	if (dir & TOP)
	{
		adjustPosition.y = adjustPosition.y - static_cast<float>(collider->GetRect()->bottom - other->GetRect()->top);
	}

	else if (dir & BOTTOM)
	{
		adjustPosition.y = adjustPosition.y + static_cast<float>(other->GetRect()->bottom - collider->GetRect()->top);
	}
	
	collider->GetTransform()->SetWorldPosition(adjustPosition);
	collider->UpdateRect();
}

void CollisionManager::Debug(ID2D1DeviceContext* render)
{
	for (auto& collider : mColliders)
	{
		if (collider->IsEnabled())
		{
			collider->Debug(render);
		}
	}
}

void CollisionManager::Release()
{
	for (auto& collider : mColliders)
	{
		delete collider;
	}

	for (auto& collider : mPendingColliderQueue)
	{
		delete collider;
	}

	mColliders.clear();
	mPendingColliderQueue.clear();
	mCollisionMap.clear();
}


/*
bool CollisionManager::CanCollide(const Collider* colliderA, const Collider* colliderB)
{
	GameObject* objA = colliderA->GetGameObject();
	GameObject* objB = colliderB->GetGameObject();

	return (objA->GetComponent<Rigidbody>() != nullptr || objB->GetComponent<Rigidbody>() != nullptr);
}
*/
