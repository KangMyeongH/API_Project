#pragma once
#include "Component.h"
class Behaviour : public Component
{
public:
	explicit Behaviour(GameObject* owner) : Component(owner), mEnabled(true) {}
	~Behaviour() override = default;

	virtual void SetEnable(const bool enabled)
	{
		mEnabled = enabled;
	}

	bool IsEnabled() const { return mEnabled; }

	void Destroy() override = 0;
protected:
	bool mEnabled;
};

