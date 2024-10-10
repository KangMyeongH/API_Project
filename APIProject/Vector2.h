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

	constexpr Vector2 operator/(const float rhs) const
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

public:
	float x;
	float y;
};