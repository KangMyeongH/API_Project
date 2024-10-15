#include "pch.h"
#include "RunState.h"

#include "Animator.h"
#include "BitMapManager.h"
#include "IdleState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "Transform.h"

void RunState::Enter()
{
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_RunningStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Running"));
}

void RunState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Down(VK_RIGHT))
	{
		mPlayer->GetAnimator()->Flip(false);
	}

	else if (mPlayer->GetKeyMgr()->Key_Down(VK_LEFT))
	{
		mPlayer->GetAnimator()->Flip(true);
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_RIGHT))
	{
		mPlayer->GetAnimator()->Flip(false);
		mPlayer->GetRigidbody()->Velocity().x = mPlayer->Speed;
	}

	else if (mPlayer->GetKeyMgr()->Key_Pressing(VK_LEFT))
	{
		mPlayer->GetAnimator()->Flip(true);
		mPlayer->GetRigidbody()->Velocity().x = -mPlayer->Speed;
	}

	else
	{
		mStateMachine->ChangeState(mPlayer->Idle);
	}

}

void RunState::LogicUpdate()
{
}

void RunState::PhysicsUpdate()
{
}

void RunState::Exit()
{
}
