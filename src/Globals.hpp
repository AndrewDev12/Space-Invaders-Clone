#pragma once

#include <SDL3/SDL_filesystem.h>
#include <string>

namespace globals
{
	namespace window
	{
		constexpr inline float aspectRatio = 2.f / 2.5f;

		inline constexpr unsigned short width = 840;
		inline constexpr unsigned short height = static_cast<unsigned short>(static_cast<float>(width) * aspectRatio);
		inline constexpr float center_x = width * 0.5f;
		inline constexpr float center_y = height * 0.5f;

		inline const char* const title = "Test Game";
	}

	namespace fonts
	{
		namespace
		{
			auto exe_path = SDL_GetBasePath();

			std::string arial_path = std::string(exe_path) += "\\assets\\fonts\\arial.ttf";
		}
		inline auto ARIAL = arial_path;
	}

	inline unsigned short max_enemies_per_row = 10;

}
