#include "pch.h"
#include "MainSceneBG.h"

#include "AnimationCurve.h"
#include "SpriteRenderer.h"
#include "TimeManager.h"

void MainSceneBG::Awake()
{
	mUpdateType = UPDATE;
}

void MainSceneBG::Update()
{
	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	float t = mCurrentTime;
	if (t >= 1.f)
	{
		mCurrentTime = 1.f;
	}
	mOwner->GetComponent<SpriteRenderer>()->SetOpacity(AnimationCurve::Lerp(0.f, 1.f, t));
}
