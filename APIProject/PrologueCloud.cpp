#include "pch.h"
#include "PrologueCloud.h"

#include "GameObjectManager.h"
#include "SpriteRenderer.h"

void PrologueCloud::Awake()
{
	mUpdateType = LATE_UPDATE;
}

void PrologueCloud::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
}

void PrologueCloud::LateUpdate()
{
	//1426 582
	D2D1_RECT_F boundary = Camera::GetInstance().GetBoundary();
	GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());

	float clampedLeft = Clamp(GetTransform()->GetWorldPosition().x - 960.f, boundary.left, boundary.right - 1920.f);
	float clampedTop = Clamp(GetTransform()->GetWorldPosition().y - 540.f, boundary.top, boundary.bottom - 1080.f + 300.f);

	GetTransform()->SetWorldPosition({ clampedLeft + 960.f, clampedTop + 540.f });

	mOwner->GetComponent<SpriteRenderer>()->SetFrame(0);
}
