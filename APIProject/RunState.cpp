#include "pch.h"
#include "RunState.h"

#include "Animator.h"
#include "BitMapManager.h"
#include "IdleState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "Transform.h"

void RunState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity().y = 0;
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_RunningStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Running"));
}

void RunState::HandleInput()
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
		mStateMachine->ChangeState(mPlayer->Idle);
	}

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SPACE))
	{
		mPlayer->GetRigidbody()->Velocity().y = -500.f;
		mPlayer->IsGrounded = false;
		mStateMachine->ChangeState(mPlayer->Jump);
	}

}

void RunState::LogicUpdate()
{
	if (!mPlayer->IsGrounded)
	{
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void RunState::PhysicsUpdate()
{
}

void RunState::Exit()
{
}
