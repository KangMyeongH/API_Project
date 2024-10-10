#pragma once
#include "GameObject.h"

class Transform;
class Component
{
public:
	explicit Component(GameObject* owner) : mOwner(owner) {}
	virtual ~Component() = default;

	bool CompareTag(const Tag tag) const { return mOwner->CompareTag(tag); }

	GameObject* 	GetGameObject() const { return mOwner; }
	Transform* 		GetTransform() const { return mOwner->GetTransform(); }
	Tag				GetTag() const { return mOwner->GetTag(); }

protected:
	GameObject* mOwner;
};

