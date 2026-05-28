
//#include <SDL3/SDL_mixer.h>

#include "Game.hpp"
#include "Projectile.hpp"
#include "Globals.hpp"
#include "Text.hpp"
#include "Enemy.hpp"
#include "AudioManager.hpp"

void Game::init()
{
	window.init();
	Text::init_text();
	AudioManager::init();
	audio_manager.init_mixer();
	audio_manager.load_sound("shoot-sound");
	audio_manager.load_sound("invaderkilled-sound");
	audio_manager.load_sound("explosion-sound");
	audio_manager.load_sound("win-sound");

	std::string high_score_file_path = SDL_GetBasePath();
	high_score_file_path += "\\assets\\high_score.txt";
	high_score_file.open(high_score_file_path);

	char s;
	high_score_file.read(&s, 3);
	high_score = std::atoi(&s);

	current_score = 0;

	inputState.keyReleased = true;

	player.init(window.get_renderer());
	player.set_pos(globals::window::center_x, globals::window::center_x * 1.5f);
	
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < globals::max_enemies_per_row; j++)
		{
			Enemy new_enemy;
			new_enemy.init(window.get_renderer());
			new_enemy.set_pos(new_enemy.get_size().x + (70 * j), 70 * i + 70);
			enemies[i].push_back(new_enemy);
		}
	}


	running = true;

}

void Game::poll_events()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			running = false;
			break;
		case SDL_EVENT_KEY_UP:
			inputState.keyReleased = !inputState.keyPressed;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.scancode == SDL_SCANCODE_ESCAPE)
				running = false;
			else if (event.key.scancode == SDL_SCANCODE_P)
				paused = !paused;

			inputState.keyPressed = !inputState.keyReleased;
			break;

		default:
			break;
		}
	}
}

void Game::update()
{

	float lastTime = SDL_GetTicks();
	float deltaTime {};

	int FPS = 0;
	int last_frame = 0;
	int current_frame = 0;

	//if (!MIX_Init())
	//	std::cout << "Mixer couldn't be initialized. SDL_Error: " << SDL_GetError() << '\n';

	//MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

	//MIX_Audio* test = MIX_LoadAudio(mixer, "assets/sounds/testsound.wav", true);

	//MIX_Track* track = MIX_CreateTrack(mixer);
	//MIX_SetTrackAudio(track, test);

	//MIX_SetTrackGain(track, 5.f);

	//MIX_PlayTrack(track, -1);

	Text bullet_count_text;
	bullet_count_text.set_color(0, 0, 0, 255)
					.set_font(globals::fonts::ARIAL, 16.f)
					.set_pos(5, 5);

	Text reload_timer_text;
	reload_timer_text.set_color(0, 0, 0, 255)
		.set_font(globals::fonts::ARIAL, 16.f)
		.set_pos(bullet_count_text.get_pos().x, bullet_count_text.get_pos().y + 20);


	Text paused_text;
	paused_text.set_color(0, 0, 0, 255)
		.set_font(globals::fonts::ARIAL, 24.f)
		.set_pos(globals::window::center_x - paused_text.get_size().x, globals::window::center_y);

	
	Text score_text;
	score_text.set_color(0, 0, 0, 255)
		.set_font(globals::fonts::ARIAL, 24.f)
		.set_pos(globals::window::center_x - paused_text.get_size().x * 1.5f, 50.f);

	Text high_score_text;
	high_score_text.set_color(0, 0, 0, 255)
		.set_font(globals::fonts::ARIAL, 24.f)
		.set_pos(globals::window::center_x - high_score_text.get_size().x * 1.5f, 20.f);

	Text won_text;
	won_text.set_color(0, 0, 0, 255)
		.set_font(globals::fonts::ARIAL, 24.f)
		.set_pos(globals::window::center_x, globals::window::center_y);
		

	Text debug_text;
	debug_text.set_color(0, 0, 0, 255).set_font(globals::fonts::ARIAL, 24.f).set_pos(100, 100);

	unsigned short remaining_enemies = globals::max_enemies_per_row * enemies.size();

	bool won = false;

	while (running)
	{
		poll_events();

		if (!paused && !won)
		{
			current_frame = SDL_GetTicks();

			window.clear_screen();


			deltaTime = Window::get_delta_time(lastTime);

			bullet_count_text.set_text("Bullets: " + std::to_string(player.get_bullets()->size()));
			reload_timer_text.set_text("Reload timer: " + std::to_string(player.get_reload_timer()));
			paused_text.set_text("Game paused");
			score_text.set_text("Score: " + std::to_string(current_score));
			high_score_text.set_text("High Score: " + std::to_string(high_score));
			won_text.set_text("You Won!");

			//debug_text.set_text(SDL_GetBasePath());

			std::list<Projectile>& bullets_ref = *player.get_bullets();

			
			for (int i = 0; i < enemies.size(); i++)
			{
				for (Enemy& enemy : enemies[i])
				{
					enemy.draw(window.get_renderer());
					enemy.update(deltaTime);
				}
			}

			for (Projectile& proj : bullets_ref)
			{
				proj.init(window.get_renderer());
				proj.draw(window);
				proj.update(deltaTime);
				
				// near row
				if (enemies[0].size() != 0)
				{

					for (Enemy& enemy : enemies[0])
					{
						if (SDL_HasRectIntersectionFloat(enemy.get_hitbox(), proj.get_hitbox()))
						{
							proj.destroy();
							enemy.destroy();
							current_score++;
							remaining_enemies--;
							audio_manager.play_sound("explosion-sound");
						}
					}
				}
				// middle row
				if (enemies[1].size() != 0)
				{

					for (Enemy& enemy : enemies[1])
					{
						if (SDL_HasRectIntersectionFloat(enemy.get_hitbox(), proj.get_hitbox()))
						{
							proj.destroy();
							enemy.destroy();
							current_score++;
							remaining_enemies--;
							audio_manager.play_sound("explosion-sound");
						}
					}
				}

				// far row
				if (enemies[2].size() != 0)
				{

					for (Enemy& enemy : enemies[2])
					{
						if (SDL_HasRectIntersectionFloat(enemy.get_hitbox(), proj.get_hitbox()))
						{
							proj.destroy();
							enemy.destroy();
							current_score++;
							remaining_enemies--;
							audio_manager.play_sound("explosion-sound");
						}
					}
				}
			}

			// move forward and to the left
			if (enemies[0].back().get_x() + enemies[0].back().get_width() * 1.5f > globals::window::width)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					for (Enemy& to_update : enemies[i])
					{
						to_update.set_y(to_update.get_y() + to_update.get_speed() * deltaTime * 20);
						to_update.set_speed(-to_update.get_speed());
						to_update.set_x(to_update.get_x() + to_update.get_speed() * deltaTime * 20);
					}
				}
			}
			// move forward and to the right
			else if (enemies[0].front().get_pos().x < enemies[0].back().get_size().x * 0.5f)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					for (Enemy& to_update : enemies[i])
					{
						to_update.set_speed(-to_update.get_speed());
						to_update.set_y(to_update.get_y() + to_update.get_speed() * deltaTime * 20);
						to_update.set_x(to_update.get_x() + to_update.get_speed() * deltaTime * 20);
					}
				}
			}

			// destroy projectiles when offscreen or collided with enemies
			std::erase_if(*player.get_bullets(), [] (Projectile& projectile)
				{
					return projectile.is_offscreen() || projectile.is_destroyed();
				});
			
			// destroy enemies when colliding with projectiles
			for (int i = 0; i < enemies.size(); i++)
			{

				std::erase_if(enemies[i], [](Enemy& enemy)
					{
						return enemy.is_destroyed();
					});
			}
			player.draw(window);
			player.update(deltaTime, &inputState);
			
			bullet_count_text.draw(window);
			reload_timer_text.draw(window);
			score_text.draw(window);
			high_score_text.draw(window);

			//debug_text.draw(window);

			if (remaining_enemies == 0)
				won = true;

			window.display();
			
			FPS++;
			if (current_frame > last_frame + 1000)
			{
				last_frame = current_frame;
				window.set_title(std::to_string(FPS).c_str());
				FPS = 0;
			}

			SDL_Delay(10);
		}
		else if (paused)
		{
			window.clear_screen();
			paused_text.draw(window);
			window.display();
		}
		else if (won)
		{
			window.clear_screen();
			won_text.draw(window);
			audio_manager.play_sound("won-sound");
	
			high_score = current_score;

			std::ofstream high_score_file_out;

			std::string high_score_file_path = SDL_GetBasePath();
			high_score_file_path += "\\assets\\high_score.txt";
			high_score_file_out.open(high_score_file_path);

			high_score_file_out << high_score;
			window.display();
		}

		if (current_score > high_score)
			high_score = current_score;

		

	}

	if (current_score > high_score)
		high_score = current_score;
	
	std::ofstream high_score_file_out;

	std::string high_score_file_path = SDL_GetBasePath();
	high_score_file_path += "\\assets\\high_score.txt";
	high_score_file_out.open(high_score_file_path);

	high_score_file_out << high_score;

	//MIX_DestroyAudio(test);
	//MIX_DestroyMixer(mixer);
	//MIX_Quit();
	//SDL_DestroyTexture(skiaTexture);

	window.cleanup();

}