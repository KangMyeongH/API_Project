#include "pch.h"
#include "GrabObject.h"

#include "BoxCollider.h"
#include "Grab.h"

void GrabObject::Init()
{
	AddComponent<SpriteRenderer>(9);
	AddComponent<BoxCollider>();
	AddComponent<Animator>();
	AddComponent<Grab>();
	GetComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
}
