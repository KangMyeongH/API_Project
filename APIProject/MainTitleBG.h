#pragma once
#include "MonoBehaviour.h"
class MainTitleBG final : public MonoBehaviour
{
public:
	explicit MainTitleBG(GameObject* owner)
		: MonoBehaviour(owner), mCurrentTime(0), mBlueLedFinish(false)
	{
	}

	void Awake() override;
	void Update() override;

private:
	Vector2 mStartPosition;
	float 	mCurrentTime;
	bool	mBlueLedFinish;

};

