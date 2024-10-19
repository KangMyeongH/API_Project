#pragma once
#include "Define.h"
class StateMachine;
class Player;

class State
{
public:
	State(Player* player, StateMachine* stateMachine, PlayerState stateType);
	virtual ~State() = default;

	virtual void Enter() = 0;
	virtual void HandleInput() = 0;
	virtual void LogicUpdate() = 0;
	virtual void PhysicsUpdate() = 0;
	virtual void Exit() = 0;
	virtual void Debug(ID2D1HwndRenderTarget* render) = 0;

	PlayerState GetType() const { return mType; }

protected:
	Player* 		mPlayer;
	StateMachine* 	mStateMachine;
	PlayerState		mType;
};

