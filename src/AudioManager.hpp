#pragma once

#include <SDL3/SDL_mixer.h>
#include <unordered_map>

class AudioManager
{
public:
	static void init();
	void init_mixer();

	void load_sound(const char* name);
	void play_sound(const char* sound);
	void set_gain(const char* sound, float gain);

	std::unordered_map<const char*, MIX_Track*> get_sounds() const;
	MIX_Mixer* get_mixer() const;
	
private:
	MIX_Mixer* mixer;
	std::unordered_map<const char*, MIX_Track*> sounds;
};

inline AudioManager audio_manager;