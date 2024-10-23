#pragma once
#include "State.h"
class ChargeDashState : public State
{
public:
	ChargeDashState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mTarget(nullptr), mChargeCurrentTime(0), mChargeDurationTime(.6f),
		  mRange(500.f),
		  mIsReady(false)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1HwndRenderTarget* render) override;

	void FindTarget();

private:
	GameObject* 	mTarget;
	float 			mChargeCurrentTime;
	float 			mChargeDurationTime;
	float 			mRange;
	bool 			mIsReady;

};

