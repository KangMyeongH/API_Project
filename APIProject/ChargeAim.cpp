#include "pch.h"
#include "ChargeAim.h"

#include "GameObject.h"

void ChargeAim::Awake()
{
	mOwner->GetComponent<Animator>()->SetEnable(false);
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
}

void ChargeAim::OnEnable()
{
	mOwner->GetComponent<Animator>()->SetEnable(true);
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(true);
	mOwner->GetComponent<Animator>()->MotionChange(mAnimation);
	mOwner->GetComponent<Animator>()->SetNextMotion(mLoopAnimation);
}

void ChargeAim::OnDisable()
{
	mOwner->GetComponent<Animator>()->SetEnable(false);
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
}

void ChargeAim::Init(AnimationInfo* aniInfo, AnimationInfo* loopAni)
{
	mAnimation = aniInfo;
	mLoopAnimation = loopAni;
}

void ChargeAim::SetInfo(const Vector2& target)
{
	mTarget = target;
	GetTransform()->SetWorldPosition(mTarget);
}
