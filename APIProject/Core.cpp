#include "pch.h"
#include "Core.h"

#include "GameObjectManager.h"
#include "MonoBehaviourManager.h"
#include "PhysicsManager.h"
#include "TimeManager.h"

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
}

void Core::Progress()
{
	mTimeMgr->Update();

	mObjMgr->ActivePending();
	mPhysicsMgr->RegisterForUpdate();
	start();
	fixedUpdate();
	physicsUpdate();
	onTrigger();
	onCollision();
	update();
	lateUpdate();
	render();
	onDestroy();

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
	// TODO : 여기에 Render 할 것들 추가
	// 예시 : mObjMgr->Render(mMemDC);

	BitBlt(mDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, mMemDC, 0, 0, SRCCOPY);
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
	mMonoBehaviourMgr->ClearDestroyQueue();
}
