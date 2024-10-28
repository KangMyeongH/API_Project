#include "pch.h"
#include "ChargeAimObj.h"

#include "BoxCollider.h"
#include "ChargeAim.h"

void ChargeAimObj::Init()
{
	mTag = ENEMY;
	mTransform.SetLocalScale({ 44.f,36.f });
	AddComponent<BoxCollider>();
	AddComponent<SpriteRenderer>(10);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<ChargeAim>();
}
