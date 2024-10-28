#pragma once
#include "MonoBehaviour.h"
class FireBirdManager final : public MonoBehaviour
{
public:
	explicit FireBirdManager(GameObject* owner) : MonoBehaviour(owner), mIsBgmLoop(false)
	{
	}

	void Awake() override;
	void Update() override;

private:
	bool mIsBgmLoop;
};

