#include "pch.h"
#include "EdgeCollider.h"

#include "BoxCollider.h"
#include "Camera.h"

bool EdgeCollider::CheckCollision(Collider* other, Vector2& contactPoint)
{
    if (other->GetType() == ColliderType::Box)
    {
        BoxCollider* otherBox = static_cast<BoxCollider*>(other);
        D2D1_RECT_F bounds = *otherBox->GetRect();
        if (LineIntersectsRect(mStart, mEnd, bounds))
        {
            contactPoint = { (mStart.x + mEnd.x) / 2, (mStart.y + mEnd.y) / 2 };
            return true;
        }
    }
    return false;
}

D2D1_RECT_F* EdgeCollider::GetRect()
{
    mRect.left = (std::min)(mStart.x, mEnd.x);
    mRect.right = (std::max)(mStart.x, mEnd.x);
    mRect.top = (std::min)(mStart.y, mEnd.y);
    mRect.bottom = (std::max)(mStart.y, mEnd.y);
    return &mRect;
}

/*
void EdgeCollider::Debug(HDC hdc)
{
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);

    MoveToEx(hdc, mStart.x, mStart.y, nullptr);
    LineTo(hdc, mEnd.x, mEnd.y);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}*/

bool EdgeCollider::LineIntersectsRect(const Vector2& start, const Vector2& end, D2D1_RECT_F rect)
{
    return (LineIntersectsLine(start, end, { rect.left, rect.top }, { rect.right, rect.top }) ||
        LineIntersectsLine(start, end, { rect.right, rect.top }, { rect.right, rect.bottom }) ||
        LineIntersectsLine(start, end, { rect.right, rect.bottom }, { rect.left, rect.bottom }) ||
        LineIntersectsLine(start, end, { rect.left, rect.bottom }, { rect.left, rect.top }));
}

bool EdgeCollider::LineIntersectsLine(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4)
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

float EdgeCollider::Direction(const Vector2& start, const Vector2& end, const Vector2& target)
{
    return (target.x - start.x) * (end.y - start.y) - (end.x - start.x) * (target.y - start.y);
}

bool EdgeCollider::OnSegment(const Vector2& start, const Vector2& end, const Vector2& target)
{
    return (std::min)(start.x, end.x) <= target.x && target.x <= (std::max)(start.x, end.x) &&
        (std::min)(start.y, end.y) <= target.y && target.y <= (std::max)(start.y, end.y);
}

void EdgeCollider::Debug(ID2D1DeviceContext* render)
{
    /*
    ID2D1SolidColorBrush* brush = nullptr;
    D2D1_RECT_F rect = { (mRect.left), (mRect.top), (mRect.right), (mRect.bottom) };

    render->CreateSolidColorBrush(ColorF(0.f, 1.f, 0.f), &brush);

	render->DrawRectangle(Camera::GetInstance().WorldToScreen(rect), brush, 1, nullptr);
    brush->Release();
    brush = nullptr;*/
}

void EdgeCollider::UpdateRect()
{
}
