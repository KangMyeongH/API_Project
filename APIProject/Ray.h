#pragma once
#include <vector>

class Transform;
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
private:
	Ray() = default;
	~Ray() = default;
public:
	Ray(const Ray&) = delete;
	Ray(Ray&&) = delete;
	Ray& operator=(const Ray&) = delete;
	Ray& operator=(Ray&&) = delete;

public:
	static Ray& GetInstance() { static Ray sMgr; return sMgr; }

	void Init(Transform* ownerTransform, float length);

	void UpdateRay();

	bool IntersectRayWithLineSegment(const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersection);

	bool IntersectRayWithBox(const RECT& rect, Vector2& intersectionPoint);

	bool IntersectRayWithEdge(const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersectionPoint);

	void Debug(ID2D1HwndRenderTarget* render);

	void Enable(const bool isEnable) { mEnable = isEnable; }

private:
	Transform* 					mOwner;
	std::vector<CollisionRay> 	mCollisions;
	Vector2 					mStartPosition;
	Vector2 					mTargetPosition;
	Vector2 					mDir;
	float						mMaxLength;
	bool 						mEnable = false;
};

