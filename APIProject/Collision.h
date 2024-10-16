#pragma once
class Collider;

class Collision
{
public:
	Collision(GameObject* other, Collider* collider, POINT contactPoint)
	: mOther(other), mCollider(collider), mContactPoint(contactPoint) {}

	GameObject* 	GetGameObject() const { return mOther; }
	Collider* 		GetCollider() const { return mCollider; }
	POINT			GetContactPoint() const { return mContactPoint; }

private:
	GameObject* mOther;
	Collider* mCollider;
	POINT mContactPoint;
};
