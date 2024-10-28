#include "pch.h"
#include "SwingJumpState.h"

#include "ChargeDashState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "StateMachine.h"

void SwingJumpState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(true);

	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_SwingJumpUp"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Rolling"));
}

void SwingJumpState::HandleInput()
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
	if (mPlayer->GetKeyMgr()->Key_Down(VK_SHIFT))
	{
		mStateMachine->ChangeState(mPlayer->ChargeDash);
	}
}

void SwingJumpState::LogicUpdate()
{
	if (mPlayer->GetRigidbody()->GetVelocity().y >= 0.f)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Roll2Fall"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Falling"));
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void SwingJumpState::PhysicsUpdate()
{
}

void SwingJumpState::Exit()
{
}

void SwingJumpState::Debug(ID2D1DeviceContext* render)
{
}
