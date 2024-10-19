#pragma once
#include "State.h"
class IdleState : public State
{
public:
	IdleState(Player* player, StateMachine* stateMachine, PlayerState stateType) : State(player, stateMachine, stateType)
	{
		
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;
	void Debug(ID2D1HwndRenderTarget* render) override;
};

