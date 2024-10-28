#pragma once
#include "Collider.h"
class EdgeCollider;

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner) : Collider(owner, ColliderType::Box), mRect{0,0,0,0} {}

	void Init() override;
	bool CheckCollision(Collider* other, Vector2& contactPoint) override;
	void UpdateRect() override;

	D2D1_RECT_F* GetRect() override;
	void Debug(ID2D1DeviceContext* render) override;

private:
	bool 		CheckEdgeCollision(EdgeCollider* edge, Vector2& contactPoint);
	bool 		LineIntersectsRect(Vector2 start, Vector2 end, D2D1_RECT_F rect);
	bool 		LineIntersectsLine(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
	float			Direction(Vector2 start, Vector2 end, Vector2 target);
	bool		OnSegment(Vector2 start, Vector2 end, Vector2 target);
	bool		AreRectsCollision(Vector2& contactPoint,const D2D1_RECT_F& rectA, const D2D1_RECT_F& rectB);
	bool		IntersectBox(D2D1_RECT_F* result, const D2D1_RECT_F* box1, const D2D1_RECT_F* box2);

private:
	D2D1_RECT_F mRect;
};