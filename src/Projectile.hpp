#pragma once

#include <SDL3/SDL.h>

#include "Vector2.hpp"

class Enemy;
class Window;

class Projectile
{
public:

	Projectile(Vector2<float> position, Vector2<short> dir);
	~Projectile();
	void init(SDL_Renderer* renderer);
	void draw(Window& window) const;
	void update(float deltaTime);
	void destroy();

	bool is_offscreen() const;
	bool is_destroyed() const;
	SDL_FRect* get_hitbox();
	SDL_FRect get_hitbox() const;

private:
	SDL_FRect hitbox;
	SDL_Texture* texture;
	Vector2<short> direction;
	Vector2<float> size;
	bool offscreen;
	bool destroyed;
	float speed;
};
