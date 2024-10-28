#pragma once
#include "MonoBehaviour.h"
class ChargeAim final : public MonoBehaviour
{
public:
	explicit ChargeAim(GameObject* owner)
		: MonoBehaviour(owner), mAnimation(nullptr), mLoopAnimation(nullptr)
	{
	}

	void Awake() override;
	void OnEnable() override;
	void OnDisable() override;

	void Init(AnimationInfo* aniInfo, AnimationInfo* loopAni);
	void SetInfo(const Vector2& target);

private:
	Vector2 		mTarget;
	AnimationInfo*	mAnimation;
	AnimationInfo* 	mLoopAnimation;

};

