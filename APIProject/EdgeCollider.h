#pragma once
#include "Collider.h"

// 매개변수로 POINT start, POINT end를 받음
class EdgeCollider : public Collider
{
public:
	EdgeCollider(GameObject* owner, Vector2 start, Vector2 end) : Collider(owner, ColliderType::Edge), mStart(start), mEnd(end)
	{
		mRect.left = (std::min)(mStart.x, mEnd.x);
		mRect.right = (std::max)(mStart.x, mEnd.x);
		mRect.top = (std::min)(mStart.y, mEnd.y);
		mRect.bottom = (std::max)(mStart.y, mEnd.y);
	}
	~EdgeCollider() override = default;

	bool 	CheckCollision(Collider* other, Vector2& contactPoint) override;

	void 	UpdateRect() override;
	D2D1_RECT_F* 	GetRect() override;

	Vector2	GetStart() const { return mStart; }
	void 	SetStart(const Vector2& start) { mStart = start; }

	Vector2 	GetEnd() const { return mEnd; }
	void 	SetEnd(const Vector2& end) { mEnd = end; }

	//void Debug(HDC hdc) override;

private:
	bool 	LineIntersectsRect(const Vector2& start, const Vector2& end, D2D1_RECT_F rect);
	bool 	LineIntersectsLine(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4);
	float 	Direction(const Vector2& start, const Vector2& end, const Vector2& target);
	bool 	OnSegment(const Vector2& start, const Vector2& end, const Vector2& target);

public:
	void Init() override {}
	void Debug(ID2D1DeviceContext* render) override;

private:
	Vector2 	mStart;
	Vector2 	mEnd;
	D2D1_RECT_F	mRect;
};
