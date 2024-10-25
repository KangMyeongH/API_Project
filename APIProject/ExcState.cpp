#include "pch.h"
#include "ExcState.h"

#include "Animator.h"
#include "GameObject.h"
#include "Grab.h"
#include "IdleState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "TimeManager.h"
#include "Transform.h"

void ExcState::Enter()
{
	mTarget = mPlayer->GetGrab()->GetTarget();
	mTarget->SetParent(mPlayer->GetTransform());
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);
}

void ExcState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_LBUTTON))
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
			mPlayer->GetRigidbody()->Velocity().x = 500.f;
		}

		else if (mPlayer->GetKeyMgr()->Key_Pressing('A'))
		{
			mPlayer->GetAnimator()->Flip(true);
			mPlayer->GetRigidbody()->Velocity().x = -500.f;
		}

		else
		{
			mPlayer->GetRigidbody()->Velocity() = { 0,0 };
		}
	}

	else if (mPlayer->GetKeyMgr()->Key_Up(VK_LBUTTON))
	{
		mTarget->SetParent(nullptr);
		mPlayer->GetRigidbody()->SetUseGravity(true);
		mPlayer->GetRigidbody()->Velocity() = CalcDirToMouse() * 500.f;
		TimeManager::GetInstance().SlowMotion(0.1f,0.1f);
		mPlayer->GetGrab()->SetIsShoot(false);
		mStateMachine->ChangeState(mPlayer->Jump);
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
}

Vector2 ExcState::CalcDirToMouse()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);
	Vector2 mousePosition = { static_cast<float>(mouse.x), static_cast<float>(mouse.y) };

	return (mPlayer->GetTransform()->GetWorldPosition() - mousePosition).Normalized();
}

void ExcState::Debug(ID2D1DeviceContext* render)
{
}
