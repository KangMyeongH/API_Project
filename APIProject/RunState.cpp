#include "pch.h"
#include "RunState.h"

#include "Animator.h"
#include "BitMapManager.h"
#include "IdleState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SoundMgr.h"
#include "StateMachine.h"
#include "Transform.h"

void RunState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity().y = 0;
	if (mStateMachine->GetPrevState()->GetType() == IDLE)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_RunStart"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Running"));
	}

	if (mStateMachine->GetPrevState()->GetType() == JUMP)
	{
		mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Land2Run"));
		mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Running"));
	}

	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
	CSoundMgr::Get_Instance()->PlayLoopSound(L"SFX_SNB_Footstep_B.wav", SOUND_PLAYER, gEffectVolume);
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
		mPlayer->GetRigidbody()->Velocity().y = -mPlayer->JumpPower;
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
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
}

void RunState::Debug(ID2D1DeviceContext* render)
{
}
 