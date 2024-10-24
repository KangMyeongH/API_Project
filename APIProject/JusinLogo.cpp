#include "pch.h"
#include "JusinLogo.h"

#include "AnimationCurve.h"
#include "GameObject.h"
#include "TimeManager.h"

void JusinLogo::Awake()
{
	mUpdateType = UPDATE;
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(0);
}

void JusinLogo::Update()
{
	if (!mIsFadeIn) FadeIn();
	else if(mIsFadeIn)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime >= 3.f)
		{
			FadeOut();
		}
	}
}

void JusinLogo::FadeIn()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
		mIsFadeIn = true;
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(0.f, 1.f, t));
}

void JusinLogo::FadeOut()
{
	float t = mCurrentTime - 3.f;
	if (t >= 1.f)
	{
		mCurrentTime = 4.f;
		mOwner->Destroy();
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(1.f, 0.f, t));
}
