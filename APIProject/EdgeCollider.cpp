#include "pch.h"
#include "EdgeCollider.h"

#include "BoxCollider.h"

bool EdgeCollider::CheckCollision(Collider* other, POINT& contactPoint)
{
    if (other->GetType() == ColliderType::Box)
    {
        BoxCollider* otherBox = static_cast<BoxCollider*>(other);
        RECT bounds = *otherBox->GetRect();
        if (LineIntersectsRect(mStart, mEnd, bounds))
        {
            contactPoint = { (mStart.x + mEnd.x) / 2, (mStart.y + mEnd.y) / 2 };
            return true;
        }
    }
    return false;
}

RECT* EdgeCollider::GetRect()
{
    mRect.left = (std::min)(mStart.x, mEnd.x);
    mRect.right = (std::max)(mStart.x, mEnd.x);
    mRect.top = (std::min)(mStart.y, mEnd.y);
    mRect.bottom = (std::max)(mStart.y, mEnd.y);
    return &mRect;
}

bool EdgeCollider::LineIntersectsRect(POINT start, POINT end, RECT rect)
{
    return (LineIntersectsLine(start, end, { rect.left, rect.top }, { rect.right, rect.top }) ||
        LineIntersectsLine(start, end, { rect.right, rect.top }, { rect.right, rect.bottom }) ||
        LineIntersectsLine(start, end, { rect.right, rect.bottom }, { rect.left, rect.bottom }) ||
        LineIntersectsLine(start, end, { rect.left, rect.bottom }, { rect.left, rect.top }));
}

bool EdgeCollider::LineIntersectsLine(POINT p1, POINT p2, POINT p3, POINT p4)
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

int EdgeCollider::Direction(POINT start, POINT end, POINT target)
{
    return (target.x - start.x) * (end.y - start.y) - (end.x - start.x) * (target.y - start.y);
}

bool EdgeCollider::OnSegment(POINT start, POINT end, POINT target)
{
    return (std::min)(start.x, end.x) <= target.x && target.x <= (std::max)(start.x, end.x) &&
        (std::min)(start.y, end.y) <= target.y && target.y <= (std::max)(start.y, end.y);
}

void EdgeCollider::UpdateRect()
{
}
