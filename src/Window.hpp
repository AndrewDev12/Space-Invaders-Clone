#pragma once

#include <array>

#include <SDL3/SDL.h>

#include "Vector2.hpp"

class Window
{
public:

	void draw_rect(Vector2<float> size, Vector2<float> pos, int r, int g, int b, int a, bool filled) const;
	void draw_pixel_Line(Vector2<float> start, Vector2<float> end, int thickness, int r, int g, int b, int a) const;
	void init();
	void set_background_color(int r, int g, int b, int a);
	void set_title(const char* new_title) const;
	void set_icon(const char* icon_path) const;
	// put at the end of main loop
	void display() const;
	void clear_screen() const;
	void cleanup() const;

	SDL_Window* get_window() const;
	SDL_Renderer* get_renderer() const;
	std::array<Uint8, 4>& get_background_color();
	unsigned short get_width() const;
	unsigned short get_height() const;
	SDL_Color get_bgcolor() const;


	static float get_delta_time(float& lastTime);

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Uint8, 4> background_color{};
	SDL_Texture* cursorTexture = nullptr;

};