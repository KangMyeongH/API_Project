#pragma once
#include "Component.h"
class Behaviour : public Component
{
public:
	explicit Behaviour(GameObject* owner) : Component(owner), mEnabled(true) {}
	~Behaviour() override = default;

	void SetEnable(const bool enabled)
	{
		mEnabled = enabled;
	}

	bool IsEnabled() const { return mEnabled; }

private:
	bool mEnabled;
};

