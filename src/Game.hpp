#pragma once

#include "Window.hpp"
#include "Player.hpp"
#include "InputState.hpp"
#include "RNG.hpp"
#include "Enemy.hpp"

#include <list>
#include <fstream>

class Game
{
public:

	void update();
	void init();

private:

	void poll_events();

private:

	Window window;
	SDL_Event event;

	Player player;
	std::array<std::list<Enemy>, 3> enemies;
	InputState inputState;
	std::fstream high_score_file;

	RNG numberGenerator;

	int high_score;
	int current_score;

	bool running = false;
	bool paused = false;
};