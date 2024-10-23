#pragma once
#include "MonoBehaviour.h"
class Effect : public MonoBehaviour
{
public:
	explicit Effect(GameObject* owner)
		: MonoBehaviour(owner), mAnimation(nullptr) {}
	
	void Awake() override;
	void Start() override;
	void Update() override;

	void SetEffect(Vector2 position, AnimationInfo* animation);

private:
	AnimationInfo* mAnimation;
};

