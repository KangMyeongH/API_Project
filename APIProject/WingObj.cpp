#include "pch.h"
#include "WingObj.h"

#include "FireBirdWing.h"

void WingObj::Init()
{
	AddComponent<SpriteRenderer>(4);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<FireBirdWing>();
}
