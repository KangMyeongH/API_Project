#include "pch.h"
#include "Core.h"

#include "GameObjectManager.h"

void Core::Init(const HWND& hwnd)
{
	mHwnd = hwnd;
	mHdc = GetDC(mHwnd);

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
	Rectangle(mHdc, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	mObjMgr->Render(mHdc);
}

void Core::onDestroy()
{
	mObjMgr->OnDestroy();
}
