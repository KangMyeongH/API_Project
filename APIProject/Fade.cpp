#include "pch.h"
#include "Fade.h"

#include "GameObject.h"

void Fade::Awake()
{
	mUpdateType = LATE_UPDATE;
}

void Fade::Start()
{
	mSprite = mOwner->GetComponent<SpriteRenderer>();
}

void Fade::LateUpdate()
{

}

void Fade::FadeIn(float duration)
{
}

void Fade::FadeOut(float duration)
{
}
