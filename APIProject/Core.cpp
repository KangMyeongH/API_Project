#include "pch.h"
#include "Core.h"

#include "GameObjectManager.h"

void Core::Init(const HWND& hwnd)
{
	mHwnd = hwnd;
	mDC = GetDC(mHwnd);

	mBit = CreateCompatibleBitmap(mDC, WIN_WIDTH, WIN_HEIGHT);
	mMemDC = CreateCompatibleDC(mDC);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(mMemDC, mBit));
	DeleteObject(hPrevBit);

	// TODO : 여기에 Manager들 바인딩
	mObjMgr = &GameObjectManager::GetInstance();
}

void Core::Progress()
{
	start();
	onCollision();
	update();
	lateUpdate();
	render();
	onDestroy();
}

void Core::start()
{
	mObjMgr->Start();
}

void Core::fixedUpdate()
{
}

void Core::onCollision()
{

}

void Core::update()
{
	mObjMgr->Update();
}

void Core::lateUpdate()
{
	mObjMgr->LateUpdate();
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
	mObjMgr->OnDestroy();
}
