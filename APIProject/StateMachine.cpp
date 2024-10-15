#include "pch.h"
#include "StateMachine.h"

#include "State.h"

void StateMachine::Initialize(State* startingState)
{
	mCurrentState = startingState;
	mPrevState = startingState;
	startingState->Enter();
}

void StateMachine::ChangeState(State* newState)
{
	mCurrentState->Exit();
	mPrevState = mCurrentState;
	mCurrentState = newState;
	newState->Enter();
}