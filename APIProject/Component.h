#pragma once
#include "GameObject.h"

class GameObject;

class Component
{
public:
	explicit Component(GameObject* owner) : mOwner(owner) {}
	virtual ~Component() = default;

	virtual void Start() {}
	virtual void Update() {}
	virtual void OnDestroy() {}

	bool CompareTag(const Tag tag) const { return mOwner->CompareTag(tag); }

	GameObject* 	GetOwner() const { return mOwner; }
	Transform& 		Transform() const { return mOwner->GetTransformRef(); }

protected:
	GameObject* mOwner;
};

