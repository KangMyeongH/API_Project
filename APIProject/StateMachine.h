#pragma once
class State;

class StateMachine
{
public:
	StateMachine() : mCurrentState(nullptr), mPrevState(nullptr)
	{
	}

	void Initialize(State* startingState);
	void ChangeState(State* newState);
	State* GetCurrentState() const { return mCurrentState; }
	State* GetPrevState() const { return mPrevState; }

private:
	State* mCurrentState;
	State* mPrevState;
};

