#include "pch.h"
#include "Core.h"

#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "MonoBehaviourManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "TitleScene.h"

void Core::Init(HWND hwnd)
{
	mHwnd = hwnd;
	mDC = GetDC(mHwnd);

	mBit = CreateCompatibleBitmap(mDC, WIN_WIDTH, WIN_HEIGHT);
	mMemDC = CreateCompatibleDC(mDC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(mMemDC, mBit));
	DeleteObject(hPrevBit);

	// TODO : ���⿡ Manager�� ���ε�
	mTimeMgr = &TimeManager::GetInstance();
	mTimeMgr->Init();
	mObjMgr = &GameObjectManager::GetInstance();
	mMonoBehaviourMgr = &MonoBehaviourManager::GetInstance();
	mPhysicsMgr = &PhysicsManager::GetInstance();
	mCollisionMgr = &CollisionManager::GetInstance();


	mSceneMgr = &SceneManager::GetInstance();
	mSceneMgr->Init(new TitleScene);
}

void Core::Progress()
{
	mTimeMgr->Update();

	mObjMgr->ActivePending();
	mPhysicsMgr->RegisterForUpdate();
	mCollisionMgr->RegisterForUpdate();
	start();
	fixedUpdate();
	physicsUpdate();
	onTrigger();
	onCollision();
	update();
	lateUpdate();
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
}

void Core::render()
{
	Rectangle(mMemDC, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	// TODO : ���⿡ Render �� �͵� �߰�
	// ���� : mObjMgr->Render(mMemDC);

	BitBlt(mDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, mMemDC, 0, 0, SRCCOPY);
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
	mMonoBehaviourMgr->ClearDestroyQueue();
}
