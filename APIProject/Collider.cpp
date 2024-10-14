#include "pch.h"
#include "Collider.h"

#include "CollisionManager.h"
#include "GameObject.h"

void Collider::Destroy()
{
	CollisionManager::GetInstance().RemoveCollider(this);
	mOwner->RemoveComponent(this);
}
