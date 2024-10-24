#pragma once
#include "MonoBehaviour.h"
class JusinLogo final : public MonoBehaviour
{
public:
	explicit JusinLogo(GameObject* owner)
		: MonoBehaviour(owner), mCurrentTime(0), mIsFadeIn(false)
	{
	}

	void Awake() override;
	void Update() override;

	void FadeIn();
	void FadeOut();


private:
	float 	mCurrentTime;
	bool 	mIsFadeIn;
};

