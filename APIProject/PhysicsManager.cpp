#include "pch.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"

PhysicsManager::~PhysicsManager()
{
	for (auto& rigidbody : mRigidbodies)
	{
		delete rigidbody;
	}

	for (auto& rigidbody : mPendingRigidbodyQueue)
	{
		delete rigidbody;
	}
}

void PhysicsManager::RegisterForUpdate()
{
	for (auto it = mPendingRigidbodyQueue.begin(); it != mPendingRigidbodyQueue.end();)
	{
		Rigidbody* rb = *it;

		if (rb->IsEnabled())
		{
			rb->SetPrevPosition(rb->GetGameObject()->GetTransform()->GetWorldPosition());
			registerForRigidbodyUpdate(rb);

			it = mPendingRigidbodyQueue.erase(it);
		}

		else ++it;
	}
}

void PhysicsManager::RigidbodyUpdate(const float deltaTime) const
{
	for (auto& rigidbody : mRigidbodies)
	{
		if (rigidbody->IsEnabled())
		{
			rigidbody->Update(deltaTime);
		}
	}
}

void PhysicsManager::ClearDestroyRigidbodyQueue()
{
	for (auto& obj : mDestroyRigidbodyQueue)
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
		unregisterFromRigidbodyUpdates(obj);
	}

	mDestroyRigidbodyQueue.clear();
}

void PhysicsManager::Release()
{
	for (auto& rigidbody : mRigidbodies)
	{
		delete rigidbody;
	}

	for (auto& rigidbody : mPendingRigidbodyQueue)
	{
		delete rigidbody;
	}

	mRigidbodies.clear();
	mPendingRigidbodyQueue.clear();
}
