#pragma once
#include "State.h"
class ExcDashState :public State
{
public:
	ExcDashState(Player* player, StateMachine* stateMachine, PlayerState stateType) : State(player, stateMachine, stateType) {}
	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;

private:
	Vector2 mStart;
	Vector2 mTarget;
	float mTime;
	float mCurrentTime;

};