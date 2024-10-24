#include "pch.h"
#include "Fade.h"

#include "AnimationCurve.h"
#include "GameObject.h"
#include "TimeManager.h"

void Fade::Awake()
{
	mUpdateType = LATE_UPDATE;
}

void Fade::Start()
{
}

void Fade::LateUpdate()
{
	if (mFadeIn) FadeIn();
	if (mFadeOut) FadeOut();
}

void Fade::FadeIn()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
		mOwner->Destroy();
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(0.f, 1.f, t));
}

void Fade::FadeOut()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime / 1.f;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
		mOwner->Destroy();
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(1.f, 0.f, t));
}
