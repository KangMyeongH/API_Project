#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"

enum AttackType
{
	SHOOT,
	BOMBER,
	BEHIND_FIRE,
	BODY_ATTACK,
	RETURN
};

class FireBird final : public MonoBehaviour
{
public:
	explicit FireBird(GameObject* owner)
		: MonoBehaviour(owner), mPattern(RETURN), mPlayer(nullptr), mBaseForce(10.f), mForceFactor(2.f),
		  mMaxForce(80.f), mMaxAngle(7.5f)
	{
	}

	~FireBird() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void Debug(ID2D1HwndRenderTarget* render) override;

	AnimationInfo* FindAniInfo(const TCHAR* key);
	void ShootPattern();
	void BomberPattern();
	void BehindFirePattern();
	void BodyAttackPattern();
	void ReturnPattern();


private:
	float clamp(float value, float minValue, float maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}



private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	AttackType 	mPattern;
	GameObject* mPlayer;
	Vector2		mTargetPosition;
	Vector2		mAngle;
	float		mBaseForce;
	float		mForceFactor;
	float		mMaxForce;
	float		mMaxAngle;
};

