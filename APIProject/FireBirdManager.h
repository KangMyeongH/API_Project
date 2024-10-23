#pragma once
#include "MonoBehaviour.h"
class FireBirdManager final : public MonoBehaviour
{
public:
	FireBirdManager(GameObject* owner) : MonoBehaviour(owner), mPlatforms{ nullptr, }
	{
	}

	void Awake() override;


private:
	GameObject* mPlatforms[7];
};

