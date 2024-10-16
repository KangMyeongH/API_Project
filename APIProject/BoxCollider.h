#pragma once
#include "Collider.h"
class EdgeCollider;

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner) : Collider(owner, ColliderType::Box), mRect() {}

	void Init() override;
	bool CheckCollision(Collider* other, POINT& contactPoint) override;
	void UpdateRect() override;

	RECT* GetRect() override;
	void Debug(HDC hdc) override;

private:
	bool 		CheckEdgeCollision(EdgeCollider* edge, POINT& contactPoint);
	bool 		LineIntersectsRect(POINT start, POINT end, RECT rect);
	bool 		LineIntersectsLine(POINT p1, POINT p2, POINT p3, POINT p4);
	int			Direction(POINT start, POINT end, POINT target);
	bool		OnSegment(POINT start, POINT end, POINT target);
	bool		AreRectsCollision(POINT& contactPoint, RECT rectA, RECT rectB);

private:
	RECT mRect;
};