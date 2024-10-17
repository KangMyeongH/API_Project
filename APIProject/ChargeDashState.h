#pragma once
#include "State.h"
class ChargeDashState : public State
{
public:
	ChargeDashState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType) {}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
};

