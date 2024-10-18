#include "pch.h"
#include "ExcDashState.h"

#include "GameObject.h"
#include "Player.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "Transform.h"

void ExcDashState::Enter()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mStart = mPlayer->GetTransform()->GetWorldPosition();
	mTarget = mPlayer->GetTarget()->GetTransform()->GetWorldPosition();
}

void ExcDashState::HandleInput()
{
}

void ExcDashState::LogicUpdate()
{
}

void ExcDashState::PhysicsUpdate()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	mPlayer->GetTransform()->SetWorldPosition(Vector2::Lerp(mStart, mTarget, mCurrentTime / mTime));
}

void ExcDashState::Exit()
{
}
