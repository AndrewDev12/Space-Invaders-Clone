#include "Vector2.hpp"

#include <cmath>
#include <limits>

template <typename T>
Vector2<T>::Vector2(T cX, T cY)
	: x(cX), y(cY)
{
}

template <typename T>
Vector2<T>::Vector2()
	: x(0), y(0)
{
}

template <typename T>
T Vector2<T>::length()
{
	return std::hypot(x, y);
}

template <typename T>
void Vector2<T>::normalize()
{
	x = 1;
	y = 1;
}

template <typename T>
void Vector2<T>::reset()
{
	x = 0;
	y = 0;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(Vector2 other)
{
	return { static_cast<T>(x + other.x), static_cast<T>(y + other.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator+(T scalar)
{
	return { static_cast<T>(x + scalar), static_cast<T>(y + scalar) };
}

template <typename T>
Vector2<T> Vector2<T>::operator-(Vector2 other)
{
	return { static_cast<T>(x - other.x), static_cast<T>(y - other.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator-(T scalar)
{
	return { static_cast<T>(x - scalar), static_cast<T>(y - scalar) };
}

template <typename T>
Vector2<T> Vector2<T>::operator*(Vector2 other)
{
	return { static_cast<T>(x * other.x), static_cast<T>(y * other.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T scalar)
{
	return { static_cast<T>(x * scalar), static_cast<T>(y * scalar) };
}

template <typename T>
Vector2<T> Vector2<T>::operator/(Vector2 other)
{

	if (other.y == 0 && other.x == 0)
	{
		x = 0;
		y = 0;
	}
	else if (other.x == 0)
		x = 0;
	else if (other.y == 0)
		y = 0;

	return { static_cast<T>(x / other.x), static_cast<T>(y / other.y) };
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T scalar)
{

	if (scalar == 0)
	{
		x = 0;
		y = 0;
	}


	return { static_cast<T>(x / scalar), static_cast<T>(y / scalar) };
}

template <typename T>
bool Vector2<T>::operator==(Vector2 other)
{
	return (x == other.x && y == other.y);
}

template <>
bool Vector2<float>::operator==(Vector2 other)
{
	return (
		std::fabsf(x - other.x) <= std::numeric_limits<float>::epsilon() &&
		std::fabsf(y - other.y) <= std::numeric_limits<float>::epsilon()
		);
}

template <typename T>
bool Vector2<T>::hasEqualX(Vector2 other)
{
	return x == other.x;
}

template <>
bool Vector2<float>::hasEqualX(Vector2<float> other)
{
	return std::fabs(x - other.x) <= std::numeric_limits<float>::epsilon();
}

template <typename T>
bool Vector2<T>::hasEqualY(Vector2 other)
{
	return y == other.y;
}

template <>
bool Vector2<float>::hasEqualY(Vector2 other)
{
	return std::fabs(y - other.y) <= std::numeric_limits<float>::epsilon();
}

template struct Vector2<int>;
template struct Vector2<float>;
template struct Vector2<short>;
