#include "Projectile.hpp"

#include <string>

#include "Globals.hpp"
#include "Enemy.hpp"
#include "Window.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_image.h>


Projectile::Projectile(Vector2<float> position, Vector2<short> dir)
	: texture(nullptr), direction(dir), size{20.f, 20.f}, offscreen(false), destroyed(false), speed(50.f)
{
	hitbox.x = position.x;
	hitbox.y = position.y;
	hitbox.w = size.x;
	hitbox.h = size.y;
}

Projectile::~Projectile()
{
	SDL_DestroyTexture(texture);
}

void Projectile::init(SDL_Renderer* renderer)
{

	auto exe_path = SDL_GetBasePath();

	std::string texture_path = exe_path;
	texture_path += "\\assets\\textures\\projectile.png";

	texture = IMG_LoadTexture(renderer, texture_path.c_str());

	if (!texture)
		SDL_Log("Couldn't load texture. SDL_Error: %s\n", SDL_GetError());
}

void Projectile::draw(Window& window) const
{
	if (!offscreen && !destroyed)
		SDL_RenderTexture(window.get_renderer(), texture, nullptr, &hitbox);
}

void Projectile::update(float deltaTime)
{
	if  (!offscreen && !destroyed)
	{
		hitbox.x += speed * deltaTime * 10 * direction.x;
		hitbox.y += speed * deltaTime * 10 * direction.y;

		if (hitbox.x < 0 ||
			hitbox.x + hitbox.w > globals::window::width ||
			hitbox.y < 0 ||
			hitbox.y + hitbox.h > globals::window::height
		)
		{
			offscreen = true;
		}

	}
}

void Projectile::destroy()
{
	destroyed = true;
}

bool Projectile::is_offscreen() const
{
	return offscreen;
}

bool Projectile::is_destroyed() const
{
	return destroyed;
}

SDL_FRect* Projectile::get_hitbox()
{
	return &hitbox;
}

SDL_FRect Projectile::get_hitbox() const
{
	return hitbox;
}