#pragma once
#include "Behaviour.h"
class Collider : public Behaviour
{
public:
	explicit Collider(GameObject* owner) : Behaviour(owner) {}
};

