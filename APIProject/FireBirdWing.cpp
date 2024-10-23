#include "pch.h"
#include "FireBirdWing.h"

#include "FireBird.h"
#include "GameObjectManager.h"

void FireBirdWing::Start()
{
	mBody = GameObjectManager::GetInstance().GetGameObjectsForTag(BOSS)->front();
	mFireBird = mBody->GetComponent<FireBird>();
	mAnimationMap = mFireBird->GetAnimationMap();

	GetTransform()->SetWorldPosition(mBody->GetTransform()->GetWorldPosition());
	GetTransform()->SetParent(mBody->GetTransform());
	mFireBird->SetWing(mOwner);
}
