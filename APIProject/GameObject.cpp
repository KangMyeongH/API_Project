#include "pch.h"
#include "GameObject.h"

#include "GameObjectManager.h"

void GameObject::Destroy()
{
	GameObjectManager::GetInstance().RemoveGameObject(this);
	for (auto it = mTransform.GetChildren().begin(); it != mTransform.GetChildren().end();)
	{
		(*it)->GetGameObject()->Destroy();
	}
}
