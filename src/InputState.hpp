#pragma once

#include "Vector2.hpp"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>

struct InputState
{
	const bool* key;
	Vector2<float> mousePosition { 0, 0 };
	SDL_MouseButtonFlags mouseButton;
	bool keyPressed { false };
	bool keyReleased { false };
	bool guiOpened { false };

	void update_mouse()
	{
		key = SDL_GetKeyboardState(nullptr);

		mouseButton = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	}
};
