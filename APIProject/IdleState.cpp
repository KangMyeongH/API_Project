#include "pch.h"
#include "IdleState.h"

#include "Animator.h"
#include "BitMapManager.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "RunState.h"
#include "StateMachine.h"

void IdleState::Enter()
{
	if (mStateMachine->GetPrevState()->GetType() == RUN)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_RunningStop"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Idle"));
	}

	else
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Idle"));
	}

	mPlayer->GetRigidbody()->SetVelocity({ 0,0 });
	mPlayer->GetRigidbody()->SetUseGravity(false);
}

void IdleState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Down(VK_RIGHT))
	{
		mPlayer->GetAnimator()->Flip(false);
		mStateMachine->ChangeState(mPlayer->Run);
	}

	else if (mPlayer->GetKeyMgr()->Key_Down(VK_LEFT))
	{
		mPlayer->GetAnimator()->Flip(true);
		mStateMachine->ChangeState(mPlayer->Run);
	}

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SPACE))
	{
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void IdleState::LogicUpdate()
{

}

void IdleState::PhysicsUpdate()
{

}

void IdleState::Exit()
{

}
