#pragma once

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

public:
	Vector2() = default;
	Vector2(float nx, float ny) : x(nx), y(ny) {}
	Vector2(const Vector2& other) :x(other.x), y(other.y) {}

	float LengthSquared() const
	{
		return x * x + y * y;
	}

	bool IsNearlyZero(float epsilon = 0.01f) const
	{
		return LengthSquared() <= epsilon * epsilon;
	}

	Vector2& operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	bool operator==(const Vector2& other) const
	{
		return  x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(float s) const
	{
		return Vector2(x * s, y * s);
	}

	Vector2 operator/(float s) const
	{
		return Vector2(x * (1.0f / s), y * (1.0f / s));
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2& operator/=(float s)
	{
		const float inv = 1.0f / s;
		x *= inv;
		y *= inv;
		return *this;
	}

};

inline Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}