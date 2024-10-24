#pragma once
#include "MonoBehaviour.h"

class Mouse final : public MonoBehaviour
{
public:
	explicit Mouse(GameObject* owner)
		: MonoBehaviour(owner)
	{
	}

	void Awake() override;
	void Update() override;
};

