#pragma once

#include <string>
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_render.h>

#include "Vector2.hpp"

class Window;

class Text
{
public:
	Text() = default;

	~Text();

	static void init_text();
	Text& set_pos(float new_x, float new_y);
	Text& set_pos(Vector2<float> new_pos);
	Text& set_font(TTF_Font* new_font);
	Text& set_font(const std::string_view& path, float psize);
	Text& set_text(const std::string_view& new_text);
	Text& set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Text& set_italic();
	Text& set_bold();
	Text& set_underlined();
	Text& set_strikethrough();
	Text& set_outline(int outline);
	Text& set_normal_hinting();
	Text& set_light_hinting();
	Text& set_no_hinting();
	Text& set_mono_hinting();
	Text& set_light_subpixel_hinting();
	void draw(const Window& window);

	Vector2<float> get_pos() const;
	Vector2<float> get_size() const;
	TTF_Font* get_font() const;
	const std::string& get_text() const;

private:
	std::string text_;
	TTF_Font* font_;
	SDL_Texture* texture_;
	SDL_Surface* surface_;
	Vector2<float> pos_;
	Vector2<float> size_;
	SDL_Color color_;
};