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
#include "PrologueScene.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "SoundMgr.h"
#include "TimeManager.h"
#include "TitleScene.h"

Core::~Core()
{
	KeyManager::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
}

void Core::Init(HWND hwnd)
{
	mHwnd = hwnd;
	mDC = GetDC(mHwnd);

	mBit = CreateCompatibleBitmap(mDC, WIN_WIDTH, WIN_HEIGHT);
	mMemDC = CreateCompatibleDC(mDC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(mMemDC, mBit));
	DeleteObject(hPrevBit);

	// TODO : ���⿡ Manager�� ���ε�
	CSoundMgr::Get_Instance()->Initialize();
	mTimeMgr = &TimeManager::GetInstance();
	mTimeMgr->Init();
	mObjMgr = &GameObjectManager::GetInstance();
	mMonoBehaviourMgr = &MonoBehaviourManager::GetInstance();
	mPhysicsMgr = &PhysicsManager::GetInstance();
	mCollisionMgr = &CollisionManager::GetInstance();
	mRenderMgr = &RenderManager::GetInstance();
	mAnimatorMgr = &AnimatorManager::GetInstance();
	mSceneMgr = &SceneManager::GetInstance();
	mSceneMgr->Init(new TitleScene);
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
	mTimeMgr->FrameLimit();
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
	// TODO : ���⿡ Render �� �͵� �߰�
	// ���� : mObjMgr->Render(mMemDC);
	mRenderMgr->Rendering(mMemDC);
	mCollisionMgr->Debug(mMemDC);
	BitBlt(mDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, mMemDC, 0, 0, SRCCOPY);*/
	gDeviceContext->BeginDraw();

	mRenderMgr->Rendering(gDeviceContext);
	mCollisionMgr->Debug(gDeviceContext);
	mMonoBehaviourMgr->Debug(gDeviceContext);

	HRESULT hr = gDeviceContext->EndDraw();
	hr = gSwapChain->Present(0, 0);
}

void Core::onDestroy()
{
	mMonoBehaviourMgr->OnDestroy();
}

void Core::destroy()
{
	// GameObject �Ҹ� -> ���� ������Ʈ�� �Ҹ� ����
	mObjMgr->DestroyQueue();
	mPhysicsMgr->ClearDestroyRigidbodyQueue();
	mCollisionMgr->ClearDestroyColliderQueue();
	mRenderMgr->ClearDestroyColliderQueue();
	mAnimatorMgr->ClearDestroyAnimatorQueue();
	mMonoBehaviourMgr->ClearDestroyQueue();
}
