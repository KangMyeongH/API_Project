#include "pch.h"
#include "SNBLogo.h"

#include "AnimationCurve.h"
#include "SpriteRenderer.h"
#include "TimeManager.h"

void SNBLogo::Awake()
{
	mUpdateType = UPDATE;
}

void SNBLogo::Update()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(0.f, 1.f, t));
}
