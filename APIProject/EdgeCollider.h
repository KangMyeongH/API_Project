#pragma once
#include "Collider.h"

// 매개변수로 POINT start, POINT end를 받음
class EdgeCollider : public Collider
{
public:
	EdgeCollider(GameObject* owner, POINT start, POINT end) : Collider(owner, ColliderType::Edge), mStart(start), mEnd(end)
	{
		mRect.left = (std::min)(mStart.x, mEnd.x);
		mRect.right = (std::max)(mStart.x, mEnd.x);
		mRect.top = (std::min)(mStart.y, mEnd.y);
		mRect.bottom = (std::max)(mStart.y, mEnd.y);
	}
	~EdgeCollider() override = default;

	bool 	CheckCollision(Collider* other, POINT& contactPoint) override;

	void 	UpdateRect() override;
	RECT* 	GetRect() override;

	POINT 	GetStart() const { return mStart; }
	void 	SetStart(const POINT start) { mStart = start; }

	POINT 	GetEnd() const { return mEnd; }
	void 	SetEnd(const POINT end) { mEnd = end; }

	void Debug(HDC hdc) override;

private:
	bool 	LineIntersectsRect(POINT start, POINT end, RECT rect);
	bool 	LineIntersectsLine(POINT p1, POINT p2, POINT p3, POINT p4);
	int 	Direction(POINT start, POINT end, POINT target);
	bool 	OnSegment(POINT start, POINT end, POINT target);

public:
	void Init() override {}

private:
	POINT 	mStart;
	POINT 	mEnd;
	RECT	mRect;
};
