#include "pch.h"
#include "JumpState.h"

#include "Animator.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"

void JumpState::Enter()
{
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Jumping"));
	mPlayer->GetRigidbody()->Velocity().y = -500.f;
	mPlayer->GetRigidbody()->SetUseGravity(true);
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
}

void JumpState::LogicUpdate()
{
}

void JumpState::PhysicsUpdate()
{
}

void JumpState::Exit()
{
}
