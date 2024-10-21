#include "pch.h"
#include "JumpState.h"

#include "Animator.h"
#include "ChargeDashState.h"
#include "ClimbingState.h"
#include "IdleState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "RunState.h"
#include "StateMachine.h"

void JumpState::Enter()
{
	mFalling = false;
	mPlayer->GetRigidbody()->SetUseGravity(true);

	if (mStateMachine->GetPrevState()->GetType() == IDLE || mStateMachine->GetPrevState()->GetType() == RUN
		|| mStateMachine->GetPrevState()->GetType() == CLIMBING)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Jumping"));
	}
}

void JumpState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Down('D'))
	{
		mPlayer->GetAnimator()->Flip(false);
	}

	else if (mPlayer->GetKeyMgr()->Key_Down('A'))
	{
		mPlayer->GetAnimator()->Flip(true);
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing('D'))
	{
		mPlayer->GetAnimator()->Flip(false);
		mPlayer->GetRigidbody()->Velocity().x = mPlayer->Speed;
	}

	else if (mPlayer->GetKeyMgr()->Key_Pressing('A'))
	{
		mPlayer->GetAnimator()->Flip(true);
		mPlayer->GetRigidbody()->Velocity().x = -mPlayer->Speed;
	}
	/*
	else
	{
		if (mPlayer->GetRigidbody()->Velocity().x > 0)
		{
			mPlayer->GetRigidbody()->Velocity().x -= 25.f;
			if (mPlayer->GetRigidbody()->Velocity().x <= 0.f)
			{
				mPlayer->GetRigidbody()->Velocity().x = 0.f;
			}
		}

		else if (mPlayer->GetRigidbody()->Velocity().x < 0)
		{
			mPlayer->GetRigidbody()->Velocity().x += 25.f;
			if (mPlayer->GetRigidbody()->Velocity().x >= 0.f)
			{
				mPlayer->GetRigidbody()->Velocity().x = 0.f;
			}
		}
	}*/

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SHIFT))
	{
		mStateMachine->ChangeState(mPlayer->ChargeDash);
	}
}

void JumpState::LogicUpdate()
{
	if (mStateMachine->GetPrevState()->GetType() == IDLE || mStateMachine->GetPrevState()->GetType() == RUN)
	{
		if (mPlayer->GetRigidbody()->Velocity().y > 0 && !mFalling)
		{
			mFalling = true;
			mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_FallStart"));
			mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Falling"));
		}
	}

	else if (mStateMachine->GetPrevState()->GetType() == CHARGEDASH)
	{
		if (mPlayer->GetRigidbody()->Velocity().y > 0 && !mFalling)
		{
			mFalling = true;
			mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Falling"));
		}
	}

	if (mPlayer->IsGrounded)
	{
		if (mPlayer->GetRigidbody()->GetVelocity().x != 0)
		{
			mStateMachine->ChangeState(mPlayer->Run);
		}

		else
		{
			mStateMachine->ChangeState(mPlayer->Idle);
		}
	}

	if (mPlayer->IsClimb)
	{
		mStateMachine->ChangeState(mPlayer->Climbing);
	}
}

void JumpState::PhysicsUpdate()
{
}

void JumpState::Exit()
{
}

void JumpState::Debug(ID2D1HwndRenderTarget* render)
{
}
