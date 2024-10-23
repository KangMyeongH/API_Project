#include "pch.h"
#include "ChargeDashAttackState.h"

#include "Player.h"

void ChargeDashAttackState::Enter()
{
	// TODO : ���ο� ��� �ֱ�
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
	// TODO : �浹 ���⿡ ���� ƨ�� ������
	if (mPlayer->GetChargeTarget()->GetTransform()->GetWorldPosition().x > mPlayer->GetTransform()->GetWorldPosition().x)
	{
		mPlayer->GetRigidbody()->Velocity() = { -300.f, -400.f };
	}

	else if (mPlayer->GetChargeTarget()->GetTransform()->GetWorldPosition().x < mPlayer->GetTransform()->GetWorldPosition().x)
	{
		mPlayer->GetRigidbody()->Velocity() = { 300.f, -400.f };
	}

	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ChargeAttack"));
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);

}

void ChargeDashAttackState::Debug(ID2D1HwndRenderTarget* render)
{
}
