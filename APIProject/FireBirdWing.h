#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class FireBird;

class FireBirdWing final : public MonoBehaviour
{
public:
	explicit FireBirdWing(GameObject* owner)
		: MonoBehaviour(owner), mAnimationMap(nullptr), mBody(nullptr), mFireBird(nullptr)
	{
	}
	void Start() override;

private:
	float clamp(float value, float minValue, float maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}


private:
	std::unordered_map<const TCHAR*, AnimationInfo*>* mAnimationMap;
	GameObject* mBody;
	FireBird* mFireBird;
};

