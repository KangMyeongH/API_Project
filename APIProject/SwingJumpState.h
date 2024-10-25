#pragma once
#include "State.h"
class SwingJumpState : public State
{
public:
	SwingJumpState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType) {}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1DeviceContext* render) override;

private:
	float mCurrentTime;
	float mDurationTime;
};

