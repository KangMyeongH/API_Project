#pragma once
#include "MonoBehaviour.h"
class SpriteRenderer;

class Fade final : public MonoBehaviour
{
public:
	explicit Fade(GameObject* owner)
		: MonoBehaviour(owner), mSprite(nullptr), mCurrentTime(0), mFadeIn(false), mFadeOut(false)
	{
	}

	~Fade() override = default;

	void Awake() override;
	void Start() override;
	void LateUpdate() override;

	void FadeIn();
	void FadeOut();

	void SetFadeIn() { mFadeIn = true; }
	void SetFadeOut() { mFadeOut = true; }

private:
	SpriteRenderer* mSprite;
	float mCurrentTime;
	bool mFadeIn;
	bool mFadeOut;
};