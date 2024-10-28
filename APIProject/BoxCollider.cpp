#include "pch.h"
#include "BoxCollider.h"

#include "EdgeCollider.h"
#include "GameObject.h"

void BoxCollider::Init()
{
	UpdateRect();
}

bool BoxCollider::CheckCollision(Collider* other, Vector2& contactPoint)
{
	UpdateRect();

	if (other->GetType() == ColliderType::Box)
	{
		BoxCollider* otherBox = static_cast<BoxCollider*>(other);
		D2D1_RECT_F intersection;
		if (IntersectBox(&intersection, &mRect, otherBox->GetRect()))
		{
			contactPoint.x = (intersection.left + intersection.right) * 0.5f;
			contactPoint.y = (intersection.top + intersection.bottom) * 0.5f;
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

	mRect.left = transform->GetWorldPosition().x - transform->GetWorldScale().x * 0.5f + mOffset.x;
	mRect.right = transform->GetWorldPosition().x + transform->GetWorldScale().x * 0.5f + mOffset.x;
	mRect.top = transform->GetWorldPosition().y - transform->GetWorldScale().y * 0.5f + mOffset.y;
	mRect.bottom = transform->GetWorldPosition().y + transform->GetWorldScale().y * 0.5f + mOffset.y;
}

D2D1_RECT_F* BoxCollider::GetRect()
{
	UpdateRect();
	return &mRect;
}

void BoxCollider::Debug(ID2D1DeviceContext* render)
{
	ID2D1SolidColorBrush* brush = nullptr;
	D2D1_RECT_F rect = { static_cast<float>(mRect.left), static_cast<float>(mRect.top), static_cast<float>(mRect.right), static_cast<float>(mRect.bottom) };
	
	render->CreateSolidColorBrush(ColorF(0.f, 1.f, 0.f), &brush);
	render->DrawRectangle(Camera::GetInstance().WorldToScreen(rect), brush, 1, nullptr);
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

bool BoxCollider::CheckEdgeCollision(EdgeCollider* edge, Vector2& contactPoint)
{
	Vector2 start = edge->GetStart();
	Vector2 end = edge->GetEnd();
	if (LineIntersectsRect(start, end, mRect))
	{
		contactPoint = { (start.x + end.x) / 2, (start.y + end.y) / 2};
		return true;
	}

	return false;
}

bool BoxCollider::LineIntersectsRect(Vector2 start, Vector2 end, D2D1_RECT_F rect)
{
	return (LineIntersectsLine(start, end, { rect.left, rect.top }, { rect.right, rect.top }) ||
		LineIntersectsLine(start, end, { rect.right, rect.top }, { rect.right, rect.bottom }) ||
		LineIntersectsLine(start, end, { rect.right, rect.bottom }, { rect.left, rect.bottom }) ||
		LineIntersectsLine(start, end, { rect.left, rect.bottom }, { rect.left, rect.top }));
}

bool BoxCollider::LineIntersectsLine(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4)
{
	float d1 = Direction(p3, p4, p1);
	float d2 = Direction(p3, p4, p2);
	float d3 = Direction(p1, p2, p3);
	float d4 = Direction(p1, p2, p4);

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

float BoxCollider::Direction(Vector2 start, Vector2 end, Vector2 target)
{
	return (target.x - start.x) * (end.y - start.y) - (end.x - start.x) * (target.y - start.y);
}


bool BoxCollider::OnSegment(Vector2 start, Vector2 end, Vector2 target)
{
	return (std::min)(start.x, end.x) <= target.x && target.x <= (std::max)(start.x, end.x) &&
		(std::min)(start.y, end.y) <= target.y && target.y <= (std::max)(start.y, end.y);
}

bool BoxCollider::AreRectsCollision(Vector2& contactPoint , const D2D1_RECT_F& rectA, const D2D1_RECT_F& rectB)
{
	// 오른쪽 경계선과 왼쪽 경계선이 맞닿는 경우
	bool isTouchingHorizontally =
		(rectA.right == rectB.left || rectA.left == rectB.right) &&
		!(rectA.bottom <= rectB.top || rectA.top >= rectB.bottom);

	if (isTouchingHorizontally)
	{
		float top = (std::min)(rectA.top, rectB.top);
		float bottom = (std::max)(rectA.bottom, rectB.bottom);

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
		float left = (std::min)(rectA.left, rectB.left);
		float right = (std::max)(rectA.left, rectB.left);

		contactPoint.x = (left + right) / 2;
		if (rectA.bottom == rectB.top) contactPoint.y = rectA.bottom;
		else contactPoint.y = rectA.top;
	}

	return isTouchingHorizontally || isTouchingVertically;
}

bool BoxCollider::IntersectBox(D2D1_RECT_F* result, const D2D1_RECT_F* box1, const D2D1_RECT_F* box2)
{
	// 두 사각형의 교차 범위를 계산합니다.
	float left = (std::max)(box1->left, box2->left);
	float top = (std::max)(box1->top, box2->top);
	float right = (std::min)(box1->right, box2->right);
	float bottom = (std::min)(box1->bottom, box2->bottom);

	// 교차가 있는지 확인합니다.
	if (left < right && top < bottom) 
	{
		if (result) 
		{
			result->left = left;
			result->top = top;
			result->right = right;
			result->bottom = bottom;
		}
		return true;
	}

	return false;
}
