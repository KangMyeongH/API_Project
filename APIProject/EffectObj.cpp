#include "pch.h"
#include "EffectObj.h"

#include "Effect.h"

void EffectObj::Init()
{
	AddComponent<SpriteRenderer>(10);
	AddComponent<Animator>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
	AddComponent<Effect>();
}
