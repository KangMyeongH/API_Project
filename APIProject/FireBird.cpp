#include "pch.h"
#include "FireBird.h"

#include "GameObjectManager.h"

void FireBird::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void FireBird::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front();
}

void FireBird::FixedUpdate()
{


	Vector2 dir = mPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

	float distance = dir.Magnitude();

	float forceMagnitude = mBaseForce + (distance * mForceFactor);
	forceMagnitude = clamp(forceMagnitude, 0, mMaxForce);

	Vector2 force = dir.Normalized() * forceMagnitude / 10.f;

	GetGameObject()->GetComponent<Rigidbody>()->AddForce(force);
}

void FireBird::Update()
{
	MonoBehaviour::Update();
}
