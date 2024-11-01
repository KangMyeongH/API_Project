#pragma once
#include "MonoBehaviour.h"
class Potal final : public MonoBehaviour
{
public:
	explicit Potal(GameObject* owner)
		: MonoBehaviour(owner)
	{
	}

	void OnCollisionEnter(Collision other) override;
};

