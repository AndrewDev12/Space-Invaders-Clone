#include "Text.hpp"
#include "Window.hpp"

#include "Overloads.hpp"

void Text::init_text()
{
	if (!TTF_Init())
	{
		SDL_Log("%s\n", SDL_GetError());
	}
}

Text& Text::set_text(const std::string_view& new_text)
{
	text_ = new_text;
	size_.x = static_cast<float>(new_text.size()) * TTF_GetFontSize(font_) * 0.5f;
	return *this;
}

Text& Text::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
	return *this;
}

Text& Text::set_bold()
{
	TTF_SetFontStyle(font_, TTF_STYLE_BOLD);
	return *this;
}

Text& Text::set_italic()
{
	TTF_SetFontStyle(font_, TTF_STYLE_ITALIC);
	return *this;
}

Text& Text::set_underlined()
{
	TTF_SetFontStyle(font_, TTF_STYLE_UNDERLINE);
	return *this;
}

Text& Text::set_strikethrough()
{
	TTF_SetFontStyle(font_, TTF_STYLE_STRIKETHROUGH);
	return *this;
}

Text& Text::set_outline(int outline)
{
	TTF_SetFontOutline(font_, outline);
	return *this;
}

Text& Text::set_normal_hinting()
{
	TTF_SetFontHinting(font_, TTF_HINTING_NORMAL);
	return *this;
}

Text& Text::set_light_hinting()
{
	TTF_SetFontHinting(font_, TTF_HINTING_LIGHT);
	return *this;
}

Text& Text::set_no_hinting()
{
	TTF_SetFontHinting(font_, TTF_HINTING_NONE);
	return *this;
}

Text& Text::set_mono_hinting()
{
	TTF_SetFontHinting(font_, TTF_HINTING_MONO);
	return *this;
}

Text& Text::set_light_subpixel_hinting()
{
	TTF_SetFontHinting(font_, TTF_HINTING_LIGHT_SUBPIXEL);
	return *this;
}

void Text::draw(const Window& window)
{
	surface_ = TTF_RenderText_Blended(font_, text_.c_str(), 0, color_);
	
	texture_ = SDL_CreateTextureFromSurface(window.get_renderer(), surface_);
	/*SDL_DestroySurface(surface_);*/
	const SDL_FRect dest {.x = pos_.x, .y = pos_.y, .w  = size_.x, .h = size_.y };
	SDL_RenderTexture(window.get_renderer(), texture_, nullptr, &dest);
}

Text& Text::set_pos(float new_x, float new_y)
{
	pos_.x = new_x;
	pos_.y = new_y;
	return *this;
}

Text& Text::set_pos(Vector2<float> new_pos)
{
	pos_ = new_pos;
	return *this;
}

Text& Text::set_font(TTF_Font* new_font)
{
	font_ = new_font;
	TTF_SetFontKerning(font_, true);
	return *this;
}

Text& Text::set_font(const std::string_view& path, float psize)
{
	font_ = TTF_OpenFont(path.data(), psize);
	size_.y = psize * 1.5f;
	size_.x = psize * 1.f;
	return *this;
}

Text::~Text()
{
	TTF_CloseFont(font_);
	SDL_DestroyTexture(texture_);
}

Vector2<float> Text::get_pos() const
{
	return pos_;
}

Vector2<float> Text::get_size() const
{
	return size_;
}

TTF_Font* Text::get_font() const
{
	return font_;
}

const std::string& Text::get_text() const
{
	return text_;
}