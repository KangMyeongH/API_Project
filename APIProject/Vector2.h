#pragma once
#include "cmath"

struct Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(const float x, const float y) : x(x), y(y) {}
	~Vector2() = default;
	Vector2(const Vector2&) = default;
	Vector2(Vector2&&) = default;
	Vector2& operator=(const Vector2&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2{ x + rhs.x, y + rhs.y };
	}

	Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2{ x - rhs.x, y - rhs.y };
	}

	Vector2& operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 operator*(const float rhs) const
	{
		return Vector2{ x * rhs, y * rhs };
	}

	Vector2& operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2 operator/(const float rhs) const
	{
		return Vector2{ x / rhs, y / rhs };
	}

	Vector2& operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	Vector2 		Normalized() const
	{
		float length = Magnitude();
		if (length != 0.0f)
		{
			return *this / length;
		}
		return *this;
	}
	float 			Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	float 			SqrMagnitude() const
	{
		return x * x + y * y;
	}
	static float	Dot(const Vector2& left, const Vector2& right)
	{
		return left.x * right.x + left.y * right.y;
	}
	static float 	Distance(const Vector2 left, const Vector2 right)
	{
		return sqrt((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
	}
	static Vector2	Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return a + (b - a) * t;
	}
	// A와 B의 좌표를 받아 A에서 B로 바라보는 각도(라디안 또는 도)를 반환
	static float GetAngle(Vector2 A, Vector2 B)
	{
		// A에서 B로 가는 벡터의 차이
		float dx = B.x - A.x;
		float dy = B.y - A.y;

		// atan2를 사용하여 각도 계산 (라디안)
		float angle = atan2(dy, dx);

		// 각도를 도(degree) 단위로 변환
		float angleInDegrees = angle * (180.0f / 3.14159265f);

		return angleInDegrees;  // 도(degree) 단위의 각도 반환
	}

public:
	float x;
	float y;
};