#pragma once
class Collision
{
public:
	Collision(GameObject* other, POINT contactPoint): mOther(other), mContactPoint(contactPoint) {}

	GameObject* 	GetGameObject() const { return mOther; }
	POINT			GetContactPoint() const { return mContactPoint; }

private:
	GameObject* mOther;
	POINT mContactPoint;
};