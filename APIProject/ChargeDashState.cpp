#include "pch.h"
#include "ChargeDashState.h"

#include "Animator.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"

void ChargeDashState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeLoop"));

}

void ChargeDashState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SHIFT))
	{
		
	}

	else if (mPlayer->GetKeyMgr()->Key_Up(VK_SHIFT))
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeEnd"));
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void ChargeDashState::LogicUpdate()
{
}

void ChargeDashState::PhysicsUpdate()
{
}

void ChargeDashState::Exit()
{
}

void ChargeDashState::Debug(ID2D1HwndRenderTarget* render)
{
}
