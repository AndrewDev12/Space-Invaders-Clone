#pragma once

#include <list>
#include <SDL3/SDL.h>

#include "Vector2.hpp"
#include "Projectile.hpp"

struct InputState;
class Window;

class Player
{
public:

	Player();
	~Player();

	void init(SDL_Renderer* renderer);
	void draw(const Window& window) const;
	void update(float deltaTime, InputState* inputState);
	void shoot();
	void set_pos(Vector2<float> new_pos);
	void set_pos(float new_x, float new_y);

	SDL_Texture* get_texture() const;
	Vector2<short> get_direction() const;
	Vector2<float> get_position() const;
	Vector2<float> get_size() const;
	float get_reload_timer() const;
	float get_reload_duration() const;
	float get_reload_speed() const;
	std::list<Projectile>* get_bullets();

private:

	std::list<Projectile> bullets;
	SDL_FRect hitbox;
	Vector2<float> position;
	Vector2<float> size;
	Vector2<short> direction;
	float speed;
	bool alive;
	bool moving;
	float reload_speed;
	float reload_duration;
	float reload_timer;
	SDL_Texture* texture;

};