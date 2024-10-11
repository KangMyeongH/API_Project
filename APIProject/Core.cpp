#include "pch.h"
#include "Core.h"

#include "GameObjectManager.h"
#include "MonoBehaviourManager.h"

void Core::Init(const HWND& hwnd)
{
	mHwnd = hwnd;
	mDC = GetDC(mHwnd);

	mBit = CreateCompatibleBitmap(mDC, WIN_WIDTH, WIN_HEIGHT);
	mMemDC = CreateCompatibleDC(mDC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(mMemDC, mBit));
	DeleteObject(hPrevBit);

	// TODO : ���⿡ Manager�� ���ε�
	mObjMgr = &GameObjectManager::GetInstance();
	mMonoBehaviourMgr = &MonoBehaviourManager::GetInstance();
}

void Core::Progress()
{
	mObjMgr->ActivePending();
	start();
	onCollision();
	update();
	lateUpdate();
	render();
	onDestroy();
}

void Core::start()
{
	mMonoBehaviourMgr->Start();
}

void Core::fixedUpdate()
{
	mMonoBehaviourMgr->FixedUpdate();
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
	// TODO : ���⿡ Render �� �͵� �߰�
	// ���� : mObjMgr->Render(mMemDC);

	BitBlt(mDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, mMemDC, 0, 0, SRCCOPY);
}

void Core::onDestroy()
{
	// GameObject �Ҹ� -> ���� ������Ʈ�� �Ҹ�
	mMonoBehaviourMgr->OnDestroy();
}
