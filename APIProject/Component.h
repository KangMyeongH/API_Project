#pragma once

class GameObject;
class Transform;
class Component
{
public:
	explicit Component(GameObject* owner) : mOwner(owner) {}
	virtual ~Component() = default;

	bool 			CompareTag(Tag tag) const;

	GameObject* 	GetGameObject() const { return mOwner; }
	Transform* 		GetTransform() const;
	Tag				GetTag() const;

	virtual void 	Destroy() = 0;
protected:
	GameObject* 	mOwner;
};

