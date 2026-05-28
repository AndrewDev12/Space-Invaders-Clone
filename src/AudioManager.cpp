#include "AudioManager.hpp"

#include <filesystem>

void AudioManager::init()
{
	MIX_Init();
}

void AudioManager::init_mixer()
{
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
}

void AudioManager::load_sound(const char* name)
{
	std::string exe_path = SDL_GetBasePath();
	std::string music_path = exe_path + "\\assets\\audio\\" + name + ".wav";

	MIX_Audio* audio = MIX_LoadAudio(mixer, music_path.c_str(), true);
	MIX_Track* track = MIX_CreateTrack(mixer);

	MIX_SetTrackAudio(track, audio);
	MIX_SetTrackGain(track, .5f);

	sounds[name] = track;

}

void AudioManager::set_gain(const char* sound, float gain)
{
	MIX_SetTrackGain(sounds[sound], gain);
}

void AudioManager::play_sound(const char* sound)
{
	MIX_PlayTrack(sounds[sound], 0);
	//MIX_SetTrackGain(sounds[sound], .1f);
}

std::unordered_map<const char*, MIX_Track*> AudioManager::get_sounds() const
{
	return sounds;
}

MIX_Mixer* AudioManager::get_mixer() const
{
	return mixer;
}
