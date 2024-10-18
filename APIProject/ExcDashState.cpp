#include "pch.h"
#include "ExcDashState.h"

#include "ExcState.h"
#include "GameObject.h"
#include "Grab.h"
#include "Player.h"
#include "Rigidbody.h"
#include "StateMachine.h"
#include "TimeManager.h"
#include "Transform.h"

void ExcDashState::Enter()
{
	mCurrentTime = 0;
	mTime = 0.1f;
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mStart = mPlayer->GetTransform()->GetWorldPosition();
	mTarget = mPlayer->GetGrab()->GetTarget();
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mStart, mTarget->GetWorldPosition()) + 90.f);
}

void ExcDashState::HandleInput()
{
}

void ExcDashState::LogicUpdate()
{
	if (mCurrentTime >= mTime)
	{
		mStateMachine->ChangeState(mPlayer->Exc);
	}
}

void ExcDashState::PhysicsUpdate()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentTime >= mTime) mCurrentTime = mTime;
	mPlayer->GetTransform()->SetWorldPosition(Vector2::Lerp(mStart, mTarget->GetWorldPosition(), mCurrentTime / mTime));
}

void ExcDashState::Exit()
{
}
