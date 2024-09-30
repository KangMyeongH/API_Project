#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(): mCollider(nullptr), mTag()
{
	mTransform.Init(this);
}

/// <summary>
/// Tag �� �Լ�
/// </summary>
bool GameObject::CompareTag(const Tag tagName) const
{
	return tagName == mTag;
}

void GameObject::Destroy(GameObject* object)
{
	GameObjectManager::GetInstance().AddDestroy(object);
}

GameObjectList& GameObject::FindGameObjectsWithTag(const Tag tag)
{
	return GameObjectManager::GetInstance().GetGameObjectsByTag(tag);
}

Transform& GameObject::GetTransform()
{
	return mTransform;
}

Tag GameObject::GetTag() const
{
	return mTag;
}
