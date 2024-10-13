#pragma once
#include "Collider.h"
class EdgeCollider : public Collider
{
public:
	EdgeCollider(GameObject* owner, POINT start, POINT end) : Collider(owner, ColliderType::Edge), mStart(start), mEnd(end), mRect() {}
	~EdgeCollider() override = default;

	bool 	CheckCollision(Collider* other, POINT& contactPoint) override;

	void 	UpdateRect() override;
	RECT* 	GetRect() override;

	POINT 	GetStart() const { return mStart; }
	void 	SetStart(const POINT start) { mStart = start; }

	POINT 	GetEnd() const { return mEnd; }
	void 	SetEnd(const POINT end) { mEnd = end; }

private:
	bool 	LineIntersectsRect(POINT start, POINT end, RECT rect);
	bool 	LineIntersectsLine(POINT p1, POINT p2, POINT p3, POINT p4);
	int 	Direction(POINT start, POINT end, POINT target);
	bool 	OnSegment(POINT start, POINT end, POINT target);

private:
	POINT 	mStart;
	POINT 	mEnd;
	RECT	mRect;
};
