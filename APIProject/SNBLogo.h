#pragma once
#include "MonoBehaviour.h"
class SNBLogo final : public MonoBehaviour
{
public:
	explicit SNBLogo(GameObject* owner)
		: MonoBehaviour(owner), mCurrentTime(0)
	{
	}

	void Awake() override;
	void Update() override;

private:
	float mCurrentTime;
};

