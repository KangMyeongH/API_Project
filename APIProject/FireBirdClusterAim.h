#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class FireBirdClusterAim final : public MonoBehaviour
{
public:
	explicit FireBirdClusterAim(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr), mCurrentTime(0), mIsShoot(false)
	{
	}

	~FireBirdClusterAim() override
	{
		for (auto& ani : mAnimationMap)
		{
			delete ani.second;
		}
	}


	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;

	AnimationInfo* FindAniInfo(const TCHAR* key);

	float clamp(float value, float minValue, float maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}


private:
	GameObject* mPlayer;
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	float mCurrentTime;
	bool mIsShoot;
};

