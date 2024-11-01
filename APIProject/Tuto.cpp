#include "pch.h"
#include "Tuto.h"

#include "GameObject.h"

void Tuto::Start()
{
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
	mOwner->GetComponent<Animator>()->SetEnable(false);
}

void Tuto::OnCollisionEnter(Collision other)
{
	if (other.GetGameObject()->CompareTag(PLAYER))
	{
		mOwner->GetComponent<SpriteRenderer>()->SetEnable(true);
		mOwner->GetComponent<Animator>()->SetEnable(true);
	}
}

void Tuto::OnCollisionExit(Collision other)
{
	if (other.GetGameObject()->CompareTag(PLAYER))
	{
		mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
		mOwner->GetComponent<Animator>()->SetEnable(false);
	}
}
