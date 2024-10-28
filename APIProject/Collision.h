#pragma once
class Collider;

class Collision
{
public:
	Collision(GameObject* other, Collider* collider, Vector2 contactPoint)
	: mOther(other), mCollider(collider), mContactPoint(contactPoint) {}

	GameObject* 	GetGameObject() const { return mOther; }
	Collider* 		GetCollider() const { return mCollider; }
	Vector2			GetContactPoint() const { return mContactPoint; }

private:
	GameObject* mOther;
	Collider* mCollider;
	Vector2 mContactPoint;
};
