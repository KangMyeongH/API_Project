#pragma once
#include "Player.h"
#include "Rigidbody.h"
#include "State.h"
#include "TimeManager.h"
#include "Transform.h"

class SwingState : public State
{
public:
	SwingState(Player* player, StateMachine* stateMachine, PlayerState stateType)
		: State(player, stateMachine, stateType), mLength(0), mGravity(0), mTheta(0), mOmega(0), mMaxAddOmega(0),
		  mTime(0),
		  mMaxLineLength(250.f), mIsDash(false), mIsFinish(false), mCurrentTime(0), mMaxOmega(0.5f)
	{
	}

	void Enter() override;
	void HandleInput() override;
	void LogicUpdate() override;
	void PhysicsUpdate() override;
	void Exit() override;


	void StartSwinging();

	void Swinging();


private:
	float Clamp(float value, float min, float max)
	{
		if (min > value) return min;
		if (max < value) return max;

		return value;
	}

	float Sign(float value) { return value >= 0 ? 1.0f : -1.0f; }

	float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	float easeInOutQuint(float t)
	{
		return t < 0.5f ? 16.f * t * t * t * t * t : 1.f - pow(-2.f * t + 2.f, 5.f) / 2.f;
		//return (t == 1.0f) ? 1.0f : 1 - pow(2, -10 * t);
	}

public:
	void Debug(ID2D1HwndRenderTarget* render) override;

private:
	Vector2		mInitialVelocity;   // ó�� ���� ����� ���� �ӵ�
	Vector2 	mVelocity;        	// ������ ���ӵ�
	Vector2		mPivot;
	float 		mLength; 			// �� ����
	float		mGravity;
	float		mTheta;				// ����
	float		mOmega;				// ���ӵ�
	float		mMaxAddOmega;
	float		mTime;				// �ð� ����
	float		mMaxLineLength;		// �ִ� �� ����
	bool		mIsDash;
	bool		mIsFinish;
	float		mCurrentTime;
	float		mMaxOmega;
	bool		mRight;
	bool		mLeft;
};

