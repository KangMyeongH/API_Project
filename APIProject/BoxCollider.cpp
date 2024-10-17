#include "pch.h"
#include "BoxCollider.h"

#include "EdgeCollider.h"
#include "GameObject.h"

void BoxCollider::Init()
{
	UpdateRect();
}

bool BoxCollider::CheckCollision(Collider* other, POINT& contactPoint)
{
	UpdateRect();

	if (other->GetType() == ColliderType::Box)
	{
		BoxCollider* otherBox = static_cast<BoxCollider*>(other);
		RECT intersection;
		if (IntersectRect(&intersection, &mRect, otherBox->GetRect()))
		{
			contactPoint.x = (intersection.left + intersection.right) / 2;
			contactPoint.y = (intersection.top + intersection.bottom) / 2;
			return true;
		}

		if (AreRectsCollision(contactPoint,mRect,*otherBox->GetRect()))
		{
			return true;
		}
	}

	else if (other->GetType() == ColliderType::Edge)
	{
		EdgeCollider* otherEdge = static_cast<EdgeCollider*>(other);
		return CheckEdgeCollision(otherEdge, contactPoint);
	}

	return false;
}

void BoxCollider::UpdateRect()
{
	Transform* transform = mOwner->GetTransform();

	mRect.left = static_cast<LONG>(transform->GetWorldPosition().x - transform->GetWorldScale().x * 0.5f) + mOffset.x;
	mRect.right = static_cast<LONG>(transform->GetWorldPosition().x + transform->GetWorldScale().x * 0.5f) + mOffset.x;
	mRect.top = static_cast<LONG>(transform->GetWorldPosition().y - transform->GetWorldScale().y * 0.5f) + mOffset.y;
	mRect.bottom = static_cast<LONG>(transform->GetWorldPosition().y + transform->GetWorldScale().y * 0.5f) + mOffset.y;
}

RECT* BoxCollider::GetRect()
{
	UpdateRect();
	return &mRect;
}

void BoxCollider::Debug(ID2D1HwndRenderTarget* render)
{
	ID2D1SolidColorBrush* brush = nullptr;
	render->CreateSolidColorBrush(ColorF(0.f, 1.f, 0.f), &brush);
	render->DrawRectangle(RectF(mRect.left, mRect.top, mRect.right, mRect.bottom), brush, 1, nullptr);
	brush->Release();
	brush = nullptr;
}

/*
void BoxCollider::Debug(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	MoveToEx(hdc, mRect.left, mRect.top, nullptr);

	LineTo(hdc, mRect.right, mRect.top);
	LineTo(hdc, mRect.right, mRect.bottom);
	LineTo(hdc, mRect.left, mRect.bottom);
	LineTo(hdc, mRect.left, mRect.top);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}*/

bool BoxCollider::CheckEdgeCollision(EdgeCollider* edge, POINT& contactPoint)
{
	POINT start = edge->GetStart();
	POINT end = edge->GetEnd();
	if (LineIntersectsRect(start, end, mRect))
	{
		contactPoint = { (start.x + end.x) / 2, (start.y + end.y) / 2};
		return true;
	}

	return false;
}

bool BoxCollider::LineIntersectsRect(POINT start, POINT end, RECT rect)
{
	return (LineIntersectsLine(start, end, { rect.left, rect.top }, { rect.right, rect.top }) ||
		LineIntersectsLine(start, end, { rect.right, rect.top }, { rect.right, rect.bottom }) ||
		LineIntersectsLine(start, end, { rect.right, rect.bottom }, { rect.left, rect.bottom }) ||
		LineIntersectsLine(start, end, { rect.left, rect.bottom }, { rect.left, rect.top }));
}

bool BoxCollider::LineIntersectsLine(POINT p1, POINT p2, POINT p3, POINT p4)
{
	int d1 = Direction(p3, p4, p1);
	int d2 = Direction(p3, p4, p2);
	int d3 = Direction(p1, p2, p3);
	int d4 = Direction(p1, p2, p4);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return true;
	}

	return (d1 == 0 && OnSegment(p3, p4, p1)) ||
		(d2 == 0 && OnSegment(p3, p4, p2)) ||
		(d3 == 0 && OnSegment(p1, p2, p3)) ||
		(d4 == 0 && OnSegment(p1, p2, p4));
}

int BoxCollider::Direction(POINT start, POINT end, POINT target)
{
	return (target.x - start.x) * (end.y - start.y) - (end.x - start.x) * (target.y - start.y);
}


bool BoxCollider::OnSegment(POINT start, POINT end, POINT target)
{
	return (std::min)(start.x, end.x) <= target.x && target.x <= (std::max)(start.x, end.x) &&
		(std::min)(start.y, end.y) <= target.y && target.y <= (std::max)(start.y, end.y);
}

bool BoxCollider::AreRectsCollision(POINT& contactPoint ,RECT rectA, RECT rectB)
{
	// 오른쪽 경계선과 왼쪽 경계선이 맞닿는 경우
	bool isTouchingHorizontally =
		(rectA.right == rectB.left || rectA.left == rectB.right) &&
		!(rectA.bottom <= rectB.top || rectA.top >= rectB.bottom);

	if (isTouchingHorizontally)
	{
		int top = (std::min)(rectA.top, rectB.top);
		int bottom = (std::max)(rectA.bottom, rectB.bottom);

		if (rectA.right == rectB.left) contactPoint.x = rectA.right;
		else contactPoint.x = rectA.left;

		contactPoint.y = (top + bottom) / 2;
	}

	// 아래쪽 경계선과 위쪽 경계선이 맞닿는 경우
	bool isTouchingVertically =
		(rectA.bottom == rectB.top || rectA.top == rectB.bottom) &&
		!(rectA.right <= rectB.left || rectA.left >= rectB.right);

	if (isTouchingVertically)
	{
		int left = (std::min)(rectA.left, rectB.left);
		int right = (std::max)(rectA.left, rectB.left);

		contactPoint.x = (left + right) / 2;
		if (rectA.bottom == rectB.top) contactPoint.y = rectA.bottom;
		else contactPoint.y = rectA.top;
	}

	return isTouchingHorizontally || isTouchingVertically;
}
