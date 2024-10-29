#pragma once
#include "MonoBehaviour.h"
class PrologueSky final : public MonoBehaviour
{
public:
	explicit PrologueSky(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr)
	{
	}

	void Awake() override;
	void Start() override;
	void LateUpdate() override;


private:
	GameObject* mPlayer;
};

