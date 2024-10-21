#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init(Scene* startScene)
{
	startScene->Init();
	mCurrentScene = startScene;
}

void SceneManager::ChangeScene(Scene* scene)
{
	mPendingScene = scene;
}

void SceneManager::RegisterScene()
{
	if (mPendingScene)
	{
		delete mCurrentScene;
		mPendingScene->Init();
		mCurrentScene = mPendingScene;
	}
}

void SceneManager::Release()
{
	delete mCurrentScene;
	delete mPendingScene;
}