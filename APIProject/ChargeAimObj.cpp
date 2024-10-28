#include "pch.h"
#include "ChargeAimObj.h"
#include "ChargeAim.h"

void ChargeAimObj::Init()
{
	AddComponent<SpriteRenderer>(10);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<ChargeAim>();
}
