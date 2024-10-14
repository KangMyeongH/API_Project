#include "pch.h"
#include "PhysicsManager.h"
#include "GameObject.h"

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
