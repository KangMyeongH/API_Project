#pragma once
#include "State.h"
class Transform;

class ExcState : public State
{
public:
	ExcState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mTarget(nullptr)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;

	Vector2 CalcDirToMouse();
	void Debug(ID2D1HwndRenderTarget* render) override;

private:
	Transform* mTarget;
};

