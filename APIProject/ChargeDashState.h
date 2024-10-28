#pragma once
#include "ChargeAim.h"
#include "ChargeAimObj.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "State.h"
class ChargeDashState : public State
{
public:
	ChargeDashState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mChargeAim(nullptr), mTarget(nullptr), mAim(nullptr), mTrack(nullptr),
		  mChargeCurrentTime(0),
		  mChargeDurationTime(.25f),
		  mRange(500.f),
		  mIsReady(false)
	{
		mChargeAim = GameObjectManager::GetInstance().AddGameObject<ChargeAimObj>();
		mChargeAim->GetComponent<ChargeAim>()->Init(mPlayer->FindAniInfo(L"ChargeAim_Appear"), mPlayer->FindAniInfo(L"ChargeAim_Idle_lp"));
		mChargeAim->GetComponent<ChargeAim>()->SetEnable(false);
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1DeviceContext* render) override;

	void FindTarget();

private:
	GameObject* 	mChargeAim;
	GameObject* 	mTarget;
	GameObject* 	mAim;
	GameObject* 	mTrack;
	float 			mChargeCurrentTime;
	float 			mChargeDurationTime;
	float 			mRange;
	bool 			mIsReady;

};

