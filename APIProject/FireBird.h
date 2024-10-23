#pragma once
#include "MonoBehaviour.h"
class FireBird final : public MonoBehaviour
{
public:
	explicit FireBird(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr), mBaseForce(10.f), mForceFactor(2.f), mMaxForce(50.f)
	{
	}

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;


private:
	float clamp(float value, float minValue, float maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}



private:
	GameObject* mPlayer;
	float		mBaseForce;
	float		mForceFactor;
	float		mMaxForce;
};

