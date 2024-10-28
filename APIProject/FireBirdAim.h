#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class FireBirdAim final :
    public MonoBehaviour
{
public:
	explicit FireBirdAim(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr), mCurrentTime(0), mDurationTime(0.08f), mDurationCurrentTime(0),
		  mIsShoot(false)
	{
	}

	~FireBirdAim() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void OnEnable() override;
	void OnDisable() override;

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
	float mDurationTime;
	float mDurationCurrentTime;
	bool mIsShoot;
};

