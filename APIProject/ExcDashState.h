#pragma once
#include "State.h"
class Transform;

class ExcDashState :public State
{
public:
	ExcDashState(Player* player, StateMachine* stateMachine, PlayerState stateType) : State(player, stateMachine,
			stateType), mTarget(nullptr), mTime(0), mCurrentTime(0)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;

private:
	Vector2 mStart;
	Transform* mTarget;
	float mTime;
	float mCurrentTime;

};
