#include "pch.h"
#include "ExcState.h"

#include "Animator.h"
#include "Enemy.h"
#include "ExcAttackState.h"
#include "GameObject.h"
#include "Grab.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "TimeManager.h"
#include "Transform.h"

void ExcState::Enter()
{
	mPlayer->GetAnimator()->Flip(false);
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ExcHolding_Neu"));
	mTarget = mPlayer->GetGrab()->GetTarget();
	mTarget->SetParent(mPlayer->GetTransform());
	if (mTarget->GetGameObject()->GetComponent<Enemy>()->GetType() == EXC_FLY)
	{
		mPlayer->GetRigidbody()->SetUseGravity(true);
		mPlayer->GetRigidbody()->SetDrag(10.f);
	}
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);
}

void ExcState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_LBUTTON))
	{
		if (mPlayer->GetKeyMgr()->Key_Down('D'))
		{
			mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ExcHolding_Front"));
		}

		else if (mPlayer->GetKeyMgr()->Key_Down('A'))
		{
			mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_ExcHolding_Back"));
		}

		if (mPlayer->GetKeyMgr()->Key_Pressing('D'))
		{
			mPlayer->GetRigidbody()->Velocity().x = 500.f;
		}

		else if (mPlayer->GetKeyMgr()->Key_Pressing('A'))
		{
			mPlayer->GetRigidbody()->Velocity().x = -500.f;
		}

		else
		{
			if (mTarget->GetGameObject()->GetComponent<Enemy>()->GetType() != EXC_FLY)
			{
				mPlayer->GetRigidbody()->Velocity() = { 0,0 };
			}
		}
	}

	else if (mPlayer->GetKeyMgr()->Key_Up(VK_LBUTTON))
	{
		POINT mouse;
		GetCursorPos(&mouse);
		ScreenToClient(gHwnd, &mouse);
		Vector2 mousePosition = Camera::GetInstance().WorldToScreenMouse({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });

		mTarget->SetParent(nullptr);
		mPlayer->GetRigidbody()->SetUseGravity(false);
		Vector2 test = CalcDirToMouse();
		mPlayer->GetRigidbody()->SetDrag(0.0f);
		mPlayer->GetRigidbody()->Velocity() = test * 500.f;
		mTarget->GetGameObject()->GetComponent<Rigidbody>()->Velocity() = test * -500.f;
		TimeManager::GetInstance().SlowMotion(0.1f,0.2f);
		mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mPlayer->GetTransform()->GetWorldPosition(), mousePosition));
		mPlayer->GetGrab()->SetIsShoot(false);
		mStateMachine->ChangeState(mPlayer->ExcAttack);
		mTarget->GetGameObject()->GetComponent<Enemy>()->SetKnockBack(true);
	}

	else
	{
		//mTargetEnemy->SetParent(nullptr);
		//mStateMachine->ChangeState(mPlayer->Idle);
	}
}

void ExcState::LogicUpdate()
{
}

void ExcState::PhysicsUpdate()
{
}

void ExcState::Exit()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->SetDrag(0.f);
}

Vector2 ExcState::CalcDirToMouse()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);
	Vector2 mousePosition = Camera::GetInstance().WorldToScreenMouse({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });

	return (mousePosition - mPlayer->GetTransform()->GetWorldPosition()).Normalized();
}

void ExcState::Debug(ID2D1DeviceContext* render)
{
}
