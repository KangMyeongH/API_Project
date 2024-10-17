#include "pch.h"
#include "Ray.h"

#include "Transform.h"

void Ray::Init(Transform* ownerTransform, const float length)
{
	mOwner = ownerTransform;
	mMaxLength = length;
}

void Ray::UpdateRay()
{
	if (!mEnable) return;

	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);
	mTargetPosition = { static_cast<float>(mouse.x), static_cast<float>(mouse.y) };
	mStartPosition = mOwner->GetWorldPosition();
	mDir = (mTargetPosition - mStartPosition).Normalized();
}

bool Ray::IntersectRayWithLineSegment(const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersection)
{
	float r_px = mStartPosition.x;
	float r_py = mStartPosition.y;
	float r_dx = mDir.x;
	float r_dy = mDir.y;

	float s_px = lineStart.x;
	float s_py = lineStart.y;
	float s_dx = lineEnd.x - lineStart.x;
	float s_dy = lineEnd.y - lineStart.y;

	float t2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);
	float t1 = (s_px + s_dx * t2 - r_px) / r_dx;

	if (t1 >= 0 && t2 >= 0 && t2 <= 1) {
		// ���� ���� ���
		intersection.x = r_px + r_dx * t1;
		intersection.y = r_py + r_dy * t1;
		return true;
	}

	return false;
}

bool Ray::IntersectRayWithBox(const RECT& rect, Vector2& intersectionPoint)
{
	Vector2 intersection;
	bool hasIntersection = false;
	float closetDistance = FLT_MAX;

	// �簢���� �� ���� �������� �����Ͽ� ���� �˻�
	std::vector<std::pair<Vector2, Vector2>> edges = {
		{{static_cast<float>(rect.left), static_cast<float>(rect.top)}, {static_cast<float>(rect.right), static_cast<float>(rect.top)}},   // ����
		{{static_cast<float>(rect.right), static_cast<float>(rect.top)}, {static_cast<float>(rect.right), static_cast<float>(rect.bottom)}}, // ������
		{{static_cast<float>(rect.right), static_cast<float>(rect.bottom)}, {static_cast<float>(rect.left), static_cast<float>(rect.bottom)}}, // �Ʒ���
		{{static_cast<float>(rect.left), static_cast<float>(rect.bottom)}, {static_cast<float>(rect.left), static_cast<float>(rect.top)}}  // ����
	};

	for (const auto& edge : edges)
	{
		if (IntersectRayWithLineSegment(edge.first, edge.second, intersection))
		{
			float distance = Vector2::Distance(mStartPosition, intersection);
			if (distance < closetDistance)
			{
				closetDistance = distance;
				intersectionPoint = intersection;
				hasIntersection = true;
			}
		}
	}

	return hasIntersection;
}

bool Ray::IntersectRayWithEdge(const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersectionPoint)
{
	return IntersectRayWithLineSegment(lineStart, lineEnd, intersectionPoint);
}

void Ray::Debug(ID2D1HwndRenderTarget* render)
{
	if (!mEnable) return;
	ID2D1SolidColorBrush* brush = nullptr;
	render->CreateSolidColorBrush(ColorF(0.f, 1.f, 0.f), &brush);

	render->DrawLine(
		D2D1_POINT_2F({ mStartPosition.x,mStartPosition.y }),
		D2D1_POINT_2F({mStartPosition.x + mDir.x * mMaxLength, mStartPosition.y + mDir.y * mMaxLength}),
		brush,
		1.f,
		nullptr
	);

	brush->Release();
	brush = nullptr;
}
