#pragma once
#include <vector>

class Collider;

struct CollisionRay
{
	CollisionRay(Collider* collider, Vector2 intersectPoint, float distance)
		: Col(collider), IntersectionPoint(intersectPoint), Distance(distance) {}


	Collider* 	Col;
	Vector2		IntersectionPoint;
	float		Distance;
};

class Ray
{
public:
	Ray(Vector2 start, Vector2 target) : mStartPosition(start), mTargetPosition(target)
	{
		mDir = (mStartPosition - mTargetPosition).Normalized();
	}


private:
	Vector2 mStartPosition;
	Vector2 mTargetPosition;
	Vector2 mDir;

	std::vector<CollisionRay> mCollisions;
};

