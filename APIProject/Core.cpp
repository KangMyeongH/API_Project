#include "pch.h"
#include "Core.h"

#include "AnimatorManager.h"
#include "CollisionManager.h"
#include "FireBirdScene.h"
#include "GameObjectManager.h"
#include "KeyManager.h"
#include "MajorBossRoomScene.h"
#include "MonoBehaviourManager.h"
#include "PhysicsManager.h"
#include "Ray.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "TitleScene.h"

Core::~Core()
{
	KeyManager::Destroy_Instance();
}

void Core::Init(HWND hwnd)
{
	mHwnd = hwnd;
	mDC = GetDC(mHwnd);

	mBit = CreateCompatibleBitmap(mDC, WIN_WIDTH, WIN_HEIGHT);
	mMemDC = CreateCompatibleDC(mDC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(mMemDC, mBit));
	DeleteObject(hPrevBit);

	// TODO : 여기에 Manager들 바인딩
	mTimeMgr = &TimeManager::GetInstance();
	mTimeMgr->Init();
	mObjMgr = &GameObjectManager::GetInstance();
	mMonoBehaviourMgr = &MonoBehaviourManager::GetInstance();
	mPhysicsMgr = &PhysicsManager::GetInstance();
	mCollisionMgr = &CollisionManager::GetInstance();
	mRenderMgr = &RenderManager::GetInstance();
	mAnimatorMgr = &AnimatorManager::GetInstance();
	mSceneMgr = &SceneManager::GetInstance();
	mSceneMgr->Init(new MajorBossRoomScene);
}

void Core::Progress()
{
	mTimeMgr->Update();
	mObjMgr->ActivePending();
	mPhysicsMgr->RegisterForUpdate();
	mCollisionMgr->RegisterForUpdate();
	mRenderMgr->RegisterForUpdate();
	mAnimatorMgr->RegisterForUpdate();
	start();
	fixedUpdate();
	physicsUpdate();
	onTrigger();
	onCollision();
	update();
	lateUpdate();
	Camera::GetInstance().Update(mTimeMgr->GetDeltaTime());
	render();
	onDestroy();
	destroy();

	mSceneMgr->RegisterScene();
	//mTimeMgr->FrameLimit();
}

void Core::start()
{
	mMonoBehaviourMgr->Start();
}

void Core::fixedUpdate()
{
	mMonoBehaviourMgr->FixedUpdate();
}

void Core::physicsUpdate()
{
	mPhysicsMgr->RigidbodyUpdate(mTimeMgr->GetDeltaTime());
}

void Core::onTrigger()
{

}

void Core::onCollision()
{
	mCollisionMgr->CheckCollisions();
}

void Core::update()
{
	mMonoBehaviourMgr->Update();
}

void Core::lateUpdate()
{
	mMonoBehaviourMgr->LateUpdate();
	mAnimatorMgr->UpdateAnimator();
	KeyManager::Get_Instance()->Update_Key();
}

void Core::render()
{
	/*
	Rectangle(mMemDC, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	// TODO : 여기에 Render 할 것들 추가
	// 예시 : mObjMgr->Render(mMemDC);
	mRenderMgr->Rendering(mMemDC);
	mCollisionMgr->Debug(mMemDC);
	BitBlt(mDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, mMemDC, 0, 0, SRCCOPY);*/
	gRenderTarget->BeginDraw();

	mRenderMgr->Rendering(gRenderTarget);
	mCollisionMgr->Debug(gRenderTarget);
	mMonoBehaviourMgr->Debug(gRenderTarget);
	Ray::GetInstance().Debug(gRenderTarget);

	HRESULT hr = gRenderTarget->EndDraw();
}

void Core::onDestroy()
{
	mMonoBehaviourMgr->OnDestroy();
}

void Core::destroy()
{
	// GameObject 소멸 -> 각종 컴포넌트들 소멸 순서
	mObjMgr->DestroyQueue();
	mPhysicsMgr->ClearDestroyRigidbodyQueue();
	mCollisionMgr->ClearDestroyColliderQueue();
	mRenderMgr->ClearDestroyColliderQueue();
	mAnimatorMgr->ClearDestroyAnimatorQueue();
	mMonoBehaviourMgr->ClearDestroyQueue();
}
