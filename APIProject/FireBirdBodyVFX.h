#pragma once
#include "MonoBehaviour.h"
class FireBirdBodyVFX final :public MonoBehaviour
{
public:
	explicit FireBirdBodyVFX(GameObject* owner)
		: MonoBehaviour(owner), mAnimationInfo(nullptr), mTargetXPosition(0), mTargetYPosition(0), mCurrentTime(0),
		  mDelayTime(0.02f)
	{
	}

	~FireBirdBodyVFX() override { delete mAnimationInfo; }

	void Awake() override;
	void Start() override;
	void Update() override;

private:
	AnimationInfo* mAnimationInfo;
	float mTargetXPosition;
	float mTargetYPosition;
	float mCurrentTime;
	float mDelayTime;
};

