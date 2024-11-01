#pragma once
#include "MonoBehaviour.h"
class Tuto : public MonoBehaviour
{
public:
	explicit Tuto(GameObject* owner)
		: MonoBehaviour(owner) {}

	void Start() override;

	void OnCollisionEnter(Collision other) override;
	void OnCollisionExit(Collision other) override;

};

