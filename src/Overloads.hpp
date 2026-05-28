#include <SDL3/SDL_pixels.h>

Uint8 operator""_u8(unsigned long long val);

SDL_Color operator*(SDL_Color color, Uint8 scalar);