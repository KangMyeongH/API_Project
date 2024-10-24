#include "pch.h"
#include "FireBirdBodyVFX.h"

#include "Effect.h"
#include "EffectObj.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "TimeManager.h"

void FireBirdBodyVFX::Awake()
{
	mUpdateType = UPDATE;
}

void FireBirdBodyVFX::Start()
{
	mAnimationInfo = new AnimationInfo(ImageManager::GetInstance().FindImage(L"FireBirdVFX_BodyslapAlert"), 0, 20, 35, 352, 0.03f, false);

	mTargetYPosition = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front()->GetTransform()->GetWorldPosition().y;
}

void FireBirdBodyVFX::Update()
{
	if (mTargetXPosition >= 2800.f) mOwner->Destroy();

	mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
	if (mCurrentTime >= mDelayTime)
	{
		GameObjectManager::GetInstance().AddGameObject<EffectObj>()->GetComponent<Effect>()->SetEffect({ mTargetXPosition, mTargetYPosition }, mAnimationInfo);
		mTargetXPosition += 35.f;
		mCurrentTime = 0;
	}
}
