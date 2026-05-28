#include "Window.hpp"
#include "Globals.hpp"

#include <SDL3/SDL3_gfxPrimitives.h>

void Window::draw_rect(Vector2<float> size, Vector2<float> pos, int r, int g, int b, int a, bool filled) const
{
	static SDL_FRect rect
	{
		.x = pos.x,
		.y = pos.y,
		.w = size.x,
		.h = size.y
	};

	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	if (filled)
	{
		SDL_RenderFillRect(renderer, &rect);
	}
	else
	{
		SDL_RenderRect(renderer, &rect);
	}
}

void Window::draw_pixel_Line(Vector2<float> start, Vector2<float> end, int thickness, int r, int g, int b, int a) const
{
	thickLineRGBA(renderer, start.x, start.y, start.x, start.y, thickness, r, g, b, a);
}

void Window::display() const
{
	SDL_RenderPresent(renderer);
	
}

void Window::cleanup() const
{
	SDL_DestroyTexture(cursorTexture);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Window::clear_screen() const
{
	SDL_SetRenderDrawColor(renderer, background_color[0], background_color[1], background_color[2], background_color[3]);
	SDL_RenderClear(renderer);
}

void Window::init()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_SetRenderVSync(renderer, 1);

	background_color[0] = 200;
	background_color[1] = 200;
	background_color[2] = 200;
	background_color[3] = 255;

	window = SDL_CreateWindow(globals::window::title, globals::window::width, globals::window::height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, nullptr);

}

void Window::set_background_color(int r, int g, int b, int a)
{
	background_color[0] = r;
	background_color[1] = g;
	background_color[2] = b;
	background_color[3] = a;
}

void Window::set_title(const char* new_title) const
{
	SDL_SetWindowTitle(window, new_title);
}

void Window::set_icon(const char* icon_path) const
{
	SDL_SetWindowIcon(window, SDL_LoadSurface(icon_path));
}

 SDL_Window* Window::get_window() const
{
	return window;
}
SDL_Renderer* Window::get_renderer() const
{
	return renderer;
}

std::array<Uint8, 4>& Window::get_background_color()
{
	return background_color;
}

//void Window::SetBackgroundColor(const float* color) {
//	for (int i = 0; i < 4; ++i)
//		backgroundColor[i] = color[i];
//}

unsigned short Window::get_width() const
{
	return globals::window::width;
}

unsigned short Window::get_height() const
{
	return globals::window::height;
}

SDL_Color Window::get_bgcolor() const
{
	return {.r = background_color[0], .g = background_color[1], .b = background_color[2], .a = background_color[3] };
}

float Window::get_delta_time(float& lastTime)
{
	float currentTime = SDL_GetTicks();
	double deltaTime = (currentTime - lastTime) / 1000.f;
	lastTime = currentTime;
	return deltaTime;
}