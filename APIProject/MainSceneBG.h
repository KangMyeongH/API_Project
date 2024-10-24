#pragma once
#include "MonoBehaviour.h"
class MainSceneBG final : public MonoBehaviour
{
public:
	explicit MainSceneBG(GameObject* owner)
		: MonoBehaviour(owner), mCurrentTime(0)
	{
	}

	void Awake() override;
	void Update() override;

private:
	float mCurrentTime;
};

