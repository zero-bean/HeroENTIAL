#pragma once
#include <cmath>
#include <Windows.h>

struct Vector {
public:
	Vector() {};
	Vector(const float x, const float y) : x(x), y(y) {};
	Vector(const POINT point) : x((float)point.x), y((float)point.y) {};

	Vector operator+(const Vector& other) const
	{
		Vector res;
		res.x = x + other.x;
		res.y = y + other.y;

		return res;
	}

	Vector operator-(const Vector& other) const
	{
		Vector res;
		res.x = x - other.x;
		res.y = y - other.y;

		return res;
	}

	Vector operator*(const float ratio) const
	{
		Vector res;
		res.x = x * ratio;
		res.y = y * ratio;

		return res;
	}

	void operator+=(const Vector& other) 
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(const float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

public:
	inline float LengthSquared() const
	{
		return (x * x) + (y * y);
	}

	float Length() const
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 0.00000000001f)
			return;

		x /= length;
		y /= length;
	}

	float Dot(const Vector& other) const 
	{
		return (x * other.x) + (y * other.y);
	}

	float Cross(const Vector& other) const
	{
		return (x * other.y) - (y * other.x);
	}


public:
	float x = 0;
	float y = 0;
};

struct VectorInt {
public:
	VectorInt() {};
	VectorInt(const __int32 x, const __int32 y) : x(x), y(y) {};
	VectorInt(const POINT point) : x(point.x), y(point.y) {};

	VectorInt operator+(const VectorInt& other) const
	{
		VectorInt res;
		res.x = x + other.x;
		res.y = y + other.y;

		return res;
	}

	VectorInt operator-(const VectorInt& other) const
	{
		VectorInt res;
		res.x = x - other.x;
		res.y = y - other.y;

		return res;
	}

	VectorInt operator*(const __int32 ratio) const
	{
		VectorInt res;
		res.x = x * ratio;
		res.y = y * ratio;

		return res;
	}

	bool operator==(const VectorInt& other) const
	{
		return (x == other.x) && (y == other.y);
	}

	bool operator<(const VectorInt& other) const
	{
		if (x != other.x)
			return x < other.x;
		
		return y < other.y;
	}

	bool operator>(const VectorInt& other) const
	{
		if (x != other.x)
			return x > other.x;

		return y > other.y;
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}

public:
	inline __int32 LengthSquared() const
	{
		return (x * x) + (y * y);
	}

	float Length() const
	{
		return (float)::sqrt(LengthSquared());
	}

	__int32 Dot(const VectorInt& other) const
	{
		return (x * other.x) + (y * other.y);
	}

	__int32 Cross(const VectorInt& other) const
	{
		return (x * other.y) - (y * other.x);
	}


public:
	__int32 x = 0;
	__int32 y = 0;
};

using Pos = Vector;
using Vec2 = Vector;
using Vec2Int = VectorInt;