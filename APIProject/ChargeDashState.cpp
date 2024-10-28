#include "pch.h"
#include "ChargeDashState.h"

#include "Animator.h"
#include "BoxCollider.h"
#include "ChargeDashAttackState.h"
#include "Effect.h"
#include "EffectObj.h"
#include "GameObjectManager.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SoundMgr.h"
#include "StateMachine.h"
#include "TimeManager.h"

void ChargeDashState::Enter()
{
	mTarget = nullptr;
	mAim = nullptr;
	mTrack = nullptr;
	mChargeCurrentTime = 0;
	mIsReady = false;

	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeLoop"));

	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Player_ChargeDashChargeStart.wav", SOUND_PLAYER_EFFECT, gEffectVolume);


	FindTarget();
}

void ChargeDashState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SHIFT))
	{
		
	}

	else if (mPlayer->GetKeyMgr()->Key_Up(VK_SHIFT))
	{
		if (mIsReady && mTarget)
		{
			Vector2 dir = (mTarget->GetTransform()->GetWorldPosition() - mPlayer->GetTransform()->GetWorldPosition()).Normalized();

			mPlayer->GetRigidbody()->Velocity() = dir * 1500.f;

			mPlayer->SetChargeTarget(mTarget);
			mStateMachine->ChangeState(mPlayer->ChargeAttack);

			Vector2 vfxPosition = mPlayer->GetTransform()->GetWorldPosition() + dir * 5.f;
			float angle = Vector2::GetAngle(vfxPosition, mPlayer->GetTransform()->GetWorldPosition());


			GameObject* vfxDash = GameObjectManager::GetInstance().AddGameObject<EffectObj>();
			vfxDash->GetComponent<Effect>()->SetEffect(vfxPosition, mPlayer->FindAniInfo(L"VfxSNB_ChargeDash"));
			vfxDash->GetComponent<SpriteRenderer>()->SetAngle(angle - 90.f);
		}
		else
		{
			mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeEnd"));
			mStateMachine->ChangeState(mPlayer->Jump);
		}
	}
}

void ChargeDashState::LogicUpdate()
{
	mChargeCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (!mIsReady && mChargeCurrentTime >= mChargeDurationTime)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
		CSoundMgr::Get_Instance()->PlayLoopSound(L"SFX_Player_ChargeDashChargeLoop.wav", SOUND_PLAYER, gEffectVolume);
		if (mTarget)
		{
			Vector2 targetPosition = mTarget->GetTransform()->GetWorldPosition();
			float x = (targetPosition.x - mPlayer->GetTransform()->GetWorldPosition().x) * 0.5f;
			float y= (targetPosition.y - mPlayer->GetTransform()->GetWorldPosition().y) * 0.5f;

			Vector2 trackPosition = { mPlayer->GetTransform()->GetWorldPosition().x + x,  mPlayer->GetTransform()->GetWorldPosition().y + y };

			mChargeAim->GetComponent<ChargeAim>()->SetInfo(targetPosition);
			mChargeAim->GetComponent<ChargeAim>()->SetEnable(true);

			/*
			mAim = GameObjectManager::GetInstance().AddGameObject<EffectObj>();
			mAim->GetComponent<Effect>()->SetEffect(mTarget->GetTransform()->GetWorldPosition(), mPlayer->FindAniInfo(L"ChargeAim_Appear"));
			*/
			mTrack = GameObjectManager::GetInstance().AddGameObject<EffectObj>();
			mTrack->GetComponent<Effect>()->SetEffect(trackPosition, mPlayer->FindAniInfo(L"ChargeTracker_Track"));
			mTrack->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mPlayer->GetTransform()->GetWorldPosition(), targetPosition) + 90.f);

			GameObject* vfxComplete = GameObjectManager::GetInstance().AddGameObject<EffectObj>();
			vfxComplete->GetComponent<Effect>()->SetEffect(mPlayer->GetTransform()->GetWorldPosition(), mPlayer->FindAniInfo(L"VfxSNB_ChargeComplete"));

			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Player_ChargeDashChargeComplete.wav", SOUND_PLAYER_EFFECT, gEffectVolume);
		}

		mIsReady = true;
	}
}

void ChargeDashState::PhysicsUpdate()
{
}

void ChargeDashState::Exit()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
	mChargeAim->GetComponent<ChargeAim>()->SetEnable(false);

}

void ChargeDashState::Debug(ID2D1DeviceContext* render)
{
}

void ChargeDashState::FindTarget()
{
	Vector2 startPosition = mPlayer->GetTransform()->GetWorldPosition();
	GameObjectList* enemyList = GameObjectManager::GetInstance().GetGameObjectsForTag(ENEMY);
	GameObjectList* platFormList = GameObjectManager::GetInstance().GetGameObjectsForTag(PLATFORM);

	float minDistance = FLT_MAX;
	GameObject* closestTarget = nullptr;

	// °¡±î¿î Àû Å½»ö
	for (auto& enemy : *enemyList)
	{
		if (!enemy->GetComponent<BoxCollider>()->IsEnabled()) continue;
		Vector2 position = enemy->GetTransform()->GetWorldPosition();
		float distance = Vector2::Distance(startPosition, position);
		if (distance > mRange) continue;

		if (distance < minDistance)
		{
			minDistance = distance;
			closestTarget = enemy;
		}
	}

	mTarget = closestTarget;

	// °¡±î¿î ÀûÀÌ ¾øÀ» ½Ã ÇÃ·§Æû Å½»ö
	if (closestTarget) return;

	for (auto& platform : *platFormList)
	{
		if (!platform->GetComponent<BoxCollider>()->IsEnabled()) continue;
		Vector2 position = platform->GetTransform()->GetWorldPosition();
		float distance = Vector2::Distance(startPosition, position);
		if (distance > mRange) continue;

		if (distance < minDistance)
		{
			minDistance = distance;
			closestTarget = platform;
		}
	}

	mTarget = closestTarget;
}
