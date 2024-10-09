#pragma once
#include "Define.h"

class GameObjectManager;
class Core
{
private:
	Core() 							= default;
	~Core() 						= default;
public:
	Core(const Core&) 				= delete;
	Core(Core&&) 					= delete;
	Core& operator=(const Core&) 	= delete;
	Core& operator=(Core&&) 		= delete;

	static Core& GetInstance() { static Core sCore; return sCore; }

public:
	void 		Init(const HWND& hwnd);
	void 		Progress();

private:
	void 		start();
	void		fixedUpdate();
	void 		onCollision();
	void 		update();
	void 		lateUpdate();
	void 		render();
	void 		onDestroy();

private:
	HWND 		mHwnd;
	HDC 		mHdc;

	// TODO : 여기에 바인딩 해줄 멤버 변수들 추가

	GameObjectManager* mObjMgr;
};

