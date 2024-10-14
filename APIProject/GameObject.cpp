#include "pch.h"
#include "GameObject.h"

#include "Collision.h"
#include "GameObjectManager.h"

void GameObject::Destroy()
{
	GameObjectManager::GetInstance().RemoveGameObject(this);
	for (auto it = mTransform.GetChildren().begin(); it != mTransform.GetChildren().end();)
	{
		(*it)->GetGameObject()->Destroy();
	}
}

void GameObject::OnCollisionEnter(Collision other)
{
	for (auto& component : mComponents)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(component);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnCollisionEnter(other);
		}
	}
}

void GameObject::OnCollisionStay(Collision other)
{
	for (auto& component : mComponents)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(component);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnCollisionStay(other);
		}
	}
}

void GameObject::OnCollisionExit(Collision other)
{
	for (auto& component : mComponents)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(component);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnCollisionExit(other);
		}
	}
}
