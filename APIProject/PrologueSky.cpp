#include "pch.h"
#include "PrologueSky.h"

#include "GameObjectManager.h"

void PrologueSky::Awake()
{
	mUpdateType = LATE_UPDATE;
}

void PrologueSky::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
}

void PrologueSky::LateUpdate()
{
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());
	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
}
