#pragma once
#include "Define.h"

class TimeManager;
class PhysicsManager;
class MonoBehaviourManager;
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
	void 		Init(HWND hwnd);
	void 		Progress();

private:
	void 		start();
	void		fixedUpdate();
	void		physicsUpdate();
	void		onTrigger();
	void 		onCollision();
	void 		update();
	void 		lateUpdate();
	void 		render();
	void 		onDestroy();
	void		destroy();

private:
	HWND 		mHwnd;
	HDC 		mDC;
	HDC			mMemDC;
	HBITMAP		mBit;

	// TODO : 여기에 바인딩 해줄 멤버 변수들 추가
	TimeManager* 			mTimeMgr;
	GameObjectManager* 		mObjMgr;
	MonoBehaviourManager* 	mMonoBehaviourMgr;
	PhysicsManager* 		mPhysicsMgr;
};

