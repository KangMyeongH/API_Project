#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::~GameObjectManager()
{
	for (const auto& object : mActiveObjects)
	{
		delete object;
	}
}

void GameObjectManager::Init(const GameObjectList* objectList)
{
	mPendingObjects = *objectList;
	for (auto& object : mPendingObjects)
	{
		object->Init();
	}
}

void GameObjectManager::Start()
{
	if (mPendingObjects.empty()) return;

	for (auto& object : mPendingObjects)
	{
		object->Start();
		mGameObjects[object->GetTag()].push_back(object);
	}

	mActiveObjects.insert(mActiveObjects.end(), mPendingObjects.begin(), mPendingObjects.end());
	mPendingObjects.clear();
}

void GameObjectManager::Update()
{
	for (const auto& object : mActiveObjects)
	{
		object->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (const auto& object : mActiveObjects)
	{
		object->LateUpdate();
	}
}

void GameObjectManager::Render(HDC& hdc)
{
	for (const auto& object : mActiveObjects)
	{
		object->Render(hdc);
	}
}

void GameObjectManager::OnDestroy()
{
	for (auto& object : mDestroyObjects)
	{
		mActiveObjects.remove(object);
		delete object;
	}
	mDestroyObjects.clear();
}

void GameObjectManager::Release()
{
	for (const auto& object : mActiveObjects)
	{
		delete object;
	}

	mActiveObjects.clear();
	mPendingObjects.clear();
	mDestroyObjects.clear();

	for (auto& list : mGameObjects)
	{
		list.clear();
	}
}

void GameObjectManager::AddGameObject(GameObject* object)
{
	mPendingObjects.push_back(object);
}

void GameObjectManager::AddDestroy(GameObject* object)
{
	mDestroyObjects.push_back(object);
}

GameObjectList& GameObjectManager::GetGameObjectsByTag(const Tag tag)
{
	return mGameObjects[tag];
}
