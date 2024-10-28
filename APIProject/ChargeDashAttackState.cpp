#include "pch.h"
#include "ChargeDashAttackState.h"

#include "Effect.h"
#include "EffectObj.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "SoundMgr.h"
#include "TimeManager.h"

void ChargeDashAttackState::Enter()
{
	// TODO : 슬로우 모션 넣기
	TimeManager::GetInstance().SlowMotion(0.2f, 0.2f);
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_SNB_ChargeDash.wav", SOUND_PLAYER_EFFECT, gEffectVolume);
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDash"));
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mPlayer->GetTransform()->GetWorldPosition(), mPlayer->GetChargeTarget()->GetTransform()->GetWorldPosition()));
}

void ChargeDashAttackState::HandleInput()
{

}

void ChargeDashAttackState::LogicUpdate()
{

}

void ChargeDashAttackState::PhysicsUpdate()
{

}

void ChargeDashAttackState::Exit()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_SNB_ChargeAttack.wav", SOUND_PLAYER_EFFECT, gEffectVolume);

	// TODO : 충돌 방향에 따라서 튕겨 나가기
	if (mPlayer->GetChargeTarget()->GetTransform()->GetWorldPosition().x > mPlayer->GetTransform()->GetWorldPosition().x)
	{
		mPlayer->GetRigidbody()->Velocity() = { -300.f, -400.f };
	}

	else if (mPlayer->GetChargeTarget()->GetTransform()->GetWorldPosition().x < mPlayer->GetTransform()->GetWorldPosition().x)
	{
		mPlayer->GetRigidbody()->Velocity() = { 300.f, -400.f };
	}

	TimeManager::GetInstance().SlowMotion(0.2f, 0.2f);

	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeAttack"));
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);

}

void ChargeDashAttackState::Debug(ID2D1DeviceContext* render)
{
}
