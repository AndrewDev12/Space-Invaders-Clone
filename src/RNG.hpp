#pragma once

import std;


class RNG
{
public:

	RNG()
	{
		auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
		generator.seed(seed);
	}

	template <typename T>
	auto get(T min, T max) -> T
	{
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<> dis(min, max);
			return dis(generator);
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			std::uniform_real_distribution<> dis(min, max);
			return dis(generator);
		}
		else
			std::println("Invalid type\n");
	}

private:
	std::mt19937_64 generator;
};
