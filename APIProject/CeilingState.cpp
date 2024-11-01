#include "pch.h"
#include "CeilingState.h"

#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "StateMachine.h"

void CeilingState::Enter()
{
       	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_Start"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_CeilingStick_Idle"));
	mPlayer->GetRigidbody()->SetUseGravity(false);
}

void CeilingState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Down('D'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_MoveStart"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_CeilingStick_Moving"));
		mPlayer->GetAnimator()->Flip(false);
	}

	else if (mPlayer->GetKeyMgr()->Key_Down('A'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_MoveStart"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_CeilingStick_Moving"));
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
		mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	}

	if (mPlayer->GetKeyMgr()->Key_Up('D'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_MoveEnd"));
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_Idle"));
	}

	else if(mPlayer->GetKeyMgr()->Key_Up('A'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_MoveEnd"));
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_CeilingStick_Idle"));
	}


	if (mPlayer->GetKeyMgr()->Key_Down(VK_SPACE))
	{
		mPlayer->IsGrounded = false;
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void CeilingState::LogicUpdate()
{
}

void CeilingState::PhysicsUpdate()
{
}

void CeilingState::Exit()
{
}

void CeilingState::Debug(ID2D1DeviceContext* render)
{
}
