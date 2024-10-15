#include "pch.h"
#include "Player.h"

#include "BitMapManager.h"
#include "GameObject.h"
#include "IdleState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "RunState.h"
#include "StateMachine.h"

Player::~Player()
{
	delete mStateMachine;
	delete Idle;
	delete Run;
	delete Jump;

	for(auto& ani : AnimationMap)
	{
		delete ani.second;
	}
}

void Player::Start()
{
	// Manager
	mKeyMgr = KeyManager::Get_Instance();

	// GetComponent
	mRigidbody = mOwner->GetComponent<Rigidbody>();
	mTransform = GetTransform();
	mAnimator = mOwner->GetComponent<Animator>();
	mStateMachine = new StateMachine;

	// State
	Idle = new IdleState(this, mStateMachine, IDLE);
	Run = new RunState(this, mStateMachine, RUN);
	Jump = new JumpState(this, mStateMachine, JUMP);

	// Player Sprite ¹Ì¸® Ä³½Ì
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Idle.bmp", L"SNB_Idle");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Running.bmp", L"SNB_Running");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_RunningStart.bmp", L"SNB_RunningStart");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_RunningStop.bmp", L"SNB_RunningStop");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Landing.bmp", L"SNB_Landing");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Jumping.bmp", L"SNB_Jumping");
	BitMapManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Jumping.bmp", L"SNB_Jumping");


	// Player Animation Ä³½Ì
	AnimationMap.insert({ L"SNB_Idle",new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_Idle"), 0, 8, 24, 44, 0.2f, true) });
	AnimationMap.insert({ L"SNB_Running",new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_Running"), 0, 20, 44, 40, .1f, true) });
	AnimationMap.insert({ L"SNB_RunningStart",new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_RunningStart"), 0, 2, 32, 42, .1f,false) });
	AnimationMap.insert({ L"SNB_RunningStop" , new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_RunningStop"), 0, 6, 40, 44, .1f, false) });
	AnimationMap.insert({ L"SNB_Landing" , new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_Landing"), 0, 3, 62, 42, .1f, false) });
	AnimationMap.insert({ L"SNB_Jumping" , new AnimationInfo(BitMapManager::GetInstance().FindImage(L"SNB_Jumping"), 0, 6, 42, 50, .1f, true) });


	// Player ½ºÅÈ
	Speed = 500.f;


	// ½ÃÀÛÇÒ¶§ Init ÇØÁÙ State ÁöÁ¤
	mStateMachine->Initialize(Idle);
}

void Player::FixedUpdate()
{
 //mOwner->GetComponent<Animator>()->
	mStateMachine->GetCurrentState()->PhysicsUpdate();
}

void Player::Update()
{
	mStateMachine->GetCurrentState()->HandleInput();
	mStateMachine->GetCurrentState()->LogicUpdate();
}

void Player::LateUpdate()
{
}

AnimationInfo* Player::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(AnimationMap.begin(), AnimationMap.end(), tagFinder(key));

	if (iter == AnimationMap.end()) return nullptr;

	return iter->second;
}

void Player::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}
