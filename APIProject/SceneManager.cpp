#include "pch.h"
#include "SceneManager.h"

#include "Fade.h"
#include "FadeObj.h"
#include "GameObjectManager.h"
#include "Scene.h"
#include "TimeManager.h"

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
	mCurrentTime = 0;
}

void SceneManager::RegisterScene()
{
	if (mPendingScene)
	{
		GameObjectManager::GetInstance().AddGameObject<FadeObj>()->GetComponent<Fade>()->SetFadeIn();
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 1.f)
		{
			GameObjectManager::GetInstance().Release();
			MonoBehaviourManager::GetInstance().Release();
			PhysicsManager::GetInstance().Release();
			CollisionManager::GetInstance().Release();
			RenderManager::GetInstance().Release();
			AnimatorManager::GetInstance().Release();
			delete mCurrentScene;
			mPendingScene->Init();
			mCurrentScene = mPendingScene;
			mPendingScene = nullptr;
			GameObjectManager::GetInstance().AddGameObject<FadeObj>()->GetComponent<Fade>()->SetFadeOut();
		}
	}
}

void SceneManager::Release()
{
	delete mCurrentScene;
	delete mPendingScene;
}