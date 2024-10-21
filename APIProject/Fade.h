#pragma once
#include "MonoBehaviour.h"
class SpriteRenderer;

class Fade final : public MonoBehaviour
{
public:
	Fade(GameObject* owner)
		: MonoBehaviour(owner), mSprite(nullptr), mDurationTime(0), mCurrentTime(0) {}
	~Fade() override = default;

	void Awake() override;
	void Start() override;
	void LateUpdate() override;

	void FadeIn(float duration);
	void FadeOut(float duration);

private:
	SpriteRenderer* mSprite;

	float mDurationTime;
	float mCurrentTime;
};