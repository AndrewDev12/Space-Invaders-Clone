#pragma once

#include <SDL3/SDL.h>
#include "Vector2.hpp"

class Enemy
{
public:
	void init(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer) const;
	void update(float& deltaTime);
	void set_pos(float new_x, float new_y);
	void set_x(float new_x);
	void set_y(float new_y);
	void set_speed(float new_speed);
	void destroy();
	void set_move_timer_limit(float new_limit);
	void set_move_timer_step(float new_step);

	float get_move_timer() const;
	float get_move_timer_limit() const;
	float get_move_timer_step() const;
	float get_speed() const;
	float get_x() const;
	float get_y() const;
	float get_width() const;
	float get_height() const;
	Vector2<float> get_pos() const;
	Vector2<float> get_size() const;
	SDL_FRect* get_hitbox();
	SDL_FRect get_hitbox() const;
	bool is_destroyed() const;

private:
	SDL_Texture* texture{};
	SDL_FRect hitbox{};
	float move_timer{};
	float move_timer_limit{};
	float move_timer_step{};
	float speed{};
	bool destroyed;
};