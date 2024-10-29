#pragma once
#include "State.h"
class ExcAttackState : public State
{
public:
	ExcAttackState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mCurrentTime(0)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1DeviceContext* render) override;


private:
	float mCurrentTime;
};

