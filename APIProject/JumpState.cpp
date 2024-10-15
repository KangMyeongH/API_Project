#include "pch.h"
#include "JumpState.h"

#include "Animator.h"
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
