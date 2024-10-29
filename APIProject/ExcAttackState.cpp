#include "pch.h"
#include "ExcAttackState.h"

#include "JumpState.h"
#include "Player.h"
#include "SoundMgr.h"
#include "StateMachine.h"
#include "TimeManager.h"

void ExcAttackState::Enter()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_SNB_Execute01.wav", SOUND_PLAYER_EFFECT, gEffectVolume);
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ExcDash"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Roll2Fall"));
	mCurrentTime = 0;
}

void ExcAttackState::HandleInput()
{
}

void ExcAttackState::LogicUpdate()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();

	if (mCurrentTime >= 0.4f)
	{
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void ExcAttackState::PhysicsUpdate()
{
}

void ExcAttackState::Exit()
{
	mPlayer->GetRigidbody()->SetUseGravity(true);
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);
}

void ExcAttackState::Debug(ID2D1DeviceContext* render)
{
}
