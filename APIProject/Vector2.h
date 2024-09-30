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
	Vector2& operator+(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vector2& operator-(const Vector2& rhs)
	{
		x = x - rhs.x;
		y = y - rhs.y;
		return *this;
	}
	Vector2& operator*(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2 		Normalized() const
	{
		Vector2 result = *this;
		const float length = sqrt(x * x + y * y);

		if (length != 0.0f)
		{
			result.x /= length;
			result.y /= length;
		}

		return result;
	}
	float 			Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	float 			SqrMagnitude() const
	{
		return x * x + y * y;
	}
	static float 	Distance(const Vector2 left, const Vector2 right)
	{
		return sqrt((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
	}

public:
	float x;
	float y;
};