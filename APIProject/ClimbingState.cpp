#include "pch.h"
#include "ClimbingState.h"

#include "Animator.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"

void ClimbingState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };

	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_WallStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_WallSliding"));
}

void ClimbingState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Down('W'))
	{
		mPlayer->GetAnimator()->SetNextMotion(nullptr);
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_WallClimbUp"));
	}

	else if (mPlayer->GetKeyMgr()->Key_Down('S'))
	{
		mPlayer->GetAnimator()->SetNextMotion(nullptr);
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_WallClimbDown"));
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing('W'))
	{
		mPlayer->GetRigidbody()->Velocity().y = -200.f;
	}

	else if (mPlayer->GetKeyMgr()->Key_Pressing('S'))
	{
		mPlayer->GetRigidbody()->Velocity().y = 500.f;
	}

	if (mPlayer->GetKeyMgr()->Key_Up('W'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_WallSliding"));
		mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	}

	else if(mPlayer->GetKeyMgr()->Key_Up('S'))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_WallSliding"));
		mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	}

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SPACE))
	{
		mPlayer->IsClimb = false;
		if (mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->GetFlip())
		{
			mPlayer->GetRigidbody()->Velocity() = { 300.f, -200.f };
		}
		else
		{
			mPlayer->GetRigidbody()->Velocity() = { -300.f, -200.f };
		}
		mStateMachine->ChangeState(mPlayer->Jump);
	}

}

void ClimbingState::LogicUpdate()
{
	if (mPlayer->GetTransform()->GetParent() == nullptr)
	{
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void ClimbingState::PhysicsUpdate()
{
}

void ClimbingState::Exit()
{
	mPlayer->GetTransform()->SetParent(nullptr);
	mPlayer->IsClimb = false;
}

void ClimbingState::Debug(ID2D1DeviceContext* render)
{
}
