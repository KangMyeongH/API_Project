#include "pch.h"
#include "JumpState.h"

#include "Animator.h"
#include "ChargeDashState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"

void JumpState::Enter()
{
	mFalling = false;
	mPlayer->GetRigidbody()->SetUseGravity(true);

	if (mStateMachine->GetPrevState()->GetType() == IDLE || mStateMachine->GetPrevState()->GetType() == RUN)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Jumping"));
		mPlayer->GetRigidbody()->Velocity().y = -500.f;
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

	else
	{
		if (mPlayer->GetRigidbody()->Velocity().x > 0)
		{
			mPlayer->GetRigidbody()->Velocity().x -= 50.f;
			if (mPlayer->GetRigidbody()->Velocity().x <= 0.f)
			{
				mPlayer->GetRigidbody()->Velocity().x = 0.f;
			}
		}

		else if (mPlayer->GetRigidbody()->Velocity().x < 0)
		{
			mPlayer->GetRigidbody()->Velocity().x += 50.f;
			if (mPlayer->GetRigidbody()->Velocity().x >= 0.f)
			{
				mPlayer->GetRigidbody()->Velocity().x = 0.f;
			}
		}
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SHIFT))
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
}

void JumpState::PhysicsUpdate()
{
}

void JumpState::Exit()
{
}
