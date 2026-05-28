#include "Enemy.hpp"

#include <SDL3/SDL_image.h>

#include "Globals.hpp"

#include <filesystem>

void Enemy::init(SDL_Renderer* renderer)
{
	auto exe_path = SDL_GetBasePath();

	std::string texture_path = exe_path;

	texture_path += "\\assets\\textures\\enemy.png";

	texture = IMG_LoadTexture(renderer, texture_path.c_str());

	if (!texture)
		SDL_Log("Texture not loaded. Error: %s\n", SDL_GetError());

	hitbox.w = static_cast<float>(texture->w);
	hitbox.h = static_cast<float>(texture->h);
	set_pos(0, 100);

	move_timer = 0;
	move_timer_limit = 50;
	move_timer_step = 0.5f;
	speed = 100;
	destroyed = false;
}

void Enemy::draw(SDL_Renderer* renderer) const
{
	if (!destroyed)
		SDL_RenderTexture(renderer, texture, nullptr, &hitbox);
}

void Enemy::update(float& deltaTime)
{
	if (!destroyed)
	{
		move_timer += move_timer_step;

		if (move_timer > move_timer_limit)
		{
			hitbox.x += speed * deltaTime * 20;
			move_timer = 0;
		}
	}
}

void Enemy::set_pos(float new_x, float new_y)
{
	hitbox.x = new_x;
	hitbox.y = new_y;
}

void Enemy::set_x(float new_x)
{
	hitbox.x = new_x;
}

void Enemy::set_y(float new_y)
{
	hitbox.y = new_y;
}

void Enemy::set_speed(float new_speed)
{
	speed = new_speed;
}

void Enemy::set_move_timer_limit(float new_limit)
{
	move_timer_limit = new_limit;
}

void Enemy::set_move_timer_step(float new_step)
{
	move_timer_step = new_step;
}

void Enemy::destroy()
{
	destroyed = true;
}

float Enemy::get_move_timer() const
{
	return move_timer;
}

float Enemy::get_move_timer_limit() const
{
	return move_timer_limit;
}

float Enemy::get_move_timer_step() const
{
	return move_timer_step;
}

float Enemy::get_speed() const
{
	return speed;
}

float Enemy::get_x() const
{
	return hitbox.x;
}

float Enemy::get_y() const
{
	return hitbox.y;
}

float Enemy::get_width() const
{
	return hitbox.w;
}

float Enemy::get_height() const
{
	return hitbox.y;
}

Vector2<float> Enemy::get_pos() const
{
	return { hitbox.x, hitbox.y };
}

Vector2<float> Enemy::get_size() const
{
	return { hitbox.w, hitbox.y };
}

SDL_FRect* Enemy::get_hitbox()
{
	return &hitbox;
}

SDL_FRect Enemy::get_hitbox() const
{
	return hitbox;
}

bool Enemy::is_destroyed() const
{
	return destroyed;
}