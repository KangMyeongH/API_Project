#include "pch.h"
#include "ChargeDashState.h"

#include "Animator.h"
#include "ChargeDashAttackState.h"
#include "GameObjectManager.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "TimeManager.h"

void ChargeDashState::Enter()
{
	mTarget = nullptr;
	mChargeCurrentTime = 0;
	mIsReady = false;

	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeStart"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_ChargeDashChargeLoop"));

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
	if (mChargeCurrentTime >= mChargeDurationTime)
	{
		mIsReady = true;
	}
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
