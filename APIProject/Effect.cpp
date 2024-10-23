#include "pch.h"
#include "Effect.h"

#include "GameObject.h"

void Effect::Awake()
{
	mUpdateType = UPDATE;
}

void Effect::Start()
{
	mOwner->GetComponent<Animator>()->MotionChange(mAnimation);
}

void Effect::Update()
{
	if (!mAnimation) return;
	Vector2 temp = GetTransform()->GetWorldPosition();
	if (mOwner->GetComponent<Animator>()->IsFinish()) mOwner->Destroy();
}

void Effect::SetEffect(Vector2 position, AnimationInfo* animation)
{
	GetTransform()->SetWorldPosition(position);
	mAnimation = animation;
}
