#pragma once

template <typename T>
struct Vector2
{
	T x;
	T y;

	Vector2(T cX, T cY);
	Vector2();

	T length();
	void normalize();
	void reset();

	Vector2 operator+(Vector2 other);
	Vector2 operator+(T scalar);

	Vector2 operator-(Vector2 other);
	Vector2 operator-(T scalar);

	Vector2 operator*(Vector2 other);
	Vector2 operator*(T scalar);

	Vector2 operator/(Vector2 other);
	Vector2 operator/(T scalar);

	bool operator==(Vector2 other);
	bool hasEqualX(Vector2 other);
	bool hasEqualY(Vector2 other);
};

