#include "Player.hpp"

#include <filesystem>

#include "AudioManager.hpp"
#include "InputState.hpp"
#include "Globals.hpp"
#include "Window.hpp"

#include <SDL3/SDL_image.h>
#include <string>

Player::Player()
	: size{40.f, 40.f}, direction{0, 0},
	speed(30), alive(true), moving(false), reload_speed(0.1f), 
	reload_duration(8.f), reload_timer(0.f), texture(nullptr)
{
	hitbox.w = size.x;
	hitbox.h = size.y;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}

void Player::init(SDL_Renderer* renderer)
{
	
	auto exe_path = SDL_GetBasePath();

	std::string texture_path = exe_path;
	texture_path += "\\assets\\textures\\player.png";


	texture = IMG_LoadTexture(renderer, texture_path.c_str());

	if (!texture)
		SDL_Log("Couldn't load player texture. %s\n", SDL_GetError());

}

void Player::draw(const Window& window) const
{
	if (alive)
	{
		SDL_RenderTexture(window.get_renderer(), texture, nullptr, &hitbox);
	}
}

void Player::update(float deltaTime, InputState* inputState)
{
	using namespace globals;

	const static auto [width, height] = size;

	inputState->update_mouse();

	if (alive)
	{
		reload_timer += reload_speed;

		if (inputState->key[SDL_SCANCODE_A] && (hitbox.x + width > width))
		{
			//textureRect.x -= speed * deltaTime * weight * globals::gravity;
			direction = { -1, 0 };
			moving = true;
		}

		else if (inputState->key[SDL_SCANCODE_D] && (hitbox.x + width < window::width))
		{
			direction = { 1, 0 };
			moving = true;
		}

		if (inputState->key[SDL_SCANCODE_SPACE])
		{
			shoot();

		}

		if (moving)
		{
			hitbox.x += speed * deltaTime * 10 * direction.x;
			hitbox.y += speed * deltaTime * 10 * direction.y;
			moving = false;
		}
	}

}

void Player::shoot()
{

	if (reload_timer > reload_duration)
	{
		bullets.emplace_back(Vector2(hitbox.x + hitbox.w * 0.25f, hitbox.y + hitbox.h * 0.25f), Vector2<short>(0, -1));
		reload_timer = 0;
		audio_manager.play_sound("shoot-sound");
	}

}

void Player::set_pos(Vector2<float> new_pos)
{
	hitbox.x = new_pos.x;
	hitbox.y = new_pos.y;
}
void Player::set_pos(float new_x, float new_y)
{
	hitbox.x = new_x;
	hitbox.y = new_y;
};


SDL_Texture* Player::get_texture() const
{
	return texture;
}

Vector2<short> Player::get_direction() const
{
	return direction;
}

Vector2<float> Player::get_position() const
{
	return { hitbox.x, hitbox.y };
}

Vector2<float> Player::get_size() const
{
	return size;
}

std::list<Projectile>* Player::get_bullets()
{
	return &bullets;
}

float Player::get_reload_duration() const
{
	return reload_duration;
}

float Player::get_reload_speed() const
{
	return reload_speed;
}

float Player::get_reload_timer() const
{
	return reload_timer;
}