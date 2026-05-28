#include "Overloads.hpp"

Uint8 operator ""_u8(unsigned long long val)
{
	return static_cast<Uint8>(val);
}

SDL_Color operator*(SDL_Color color, auto scalar)
{
	return SDL_Color(color.r * scalar, color.g * scalar, color.b * scalar, color.a * scalar);
}