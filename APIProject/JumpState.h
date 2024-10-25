#pragma once
#include "State.h"
class JumpState : public State
{
public:
	JumpState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mFalling(false)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1DeviceContext* render) override;

private:
	bool mFalling;
};

