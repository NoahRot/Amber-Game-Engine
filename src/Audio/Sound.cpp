#include "Audio/Sound.hpp"

namespace AMB {

Sound::Sound(const std::string& path) 
: m_volume(1.0f)
{
    // Load the sound
    m_sound = Mix_LoadWAV(path.c_str());

    // Check if the sound has been loaded successfully
    if (!m_sound) {
        Logger::instance().log(Error, "Can not load sound. Sound path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        exit(EXIT_FAILURE);
    }

    volume(m_volume);
}

Sound::~Sound() {
    Mix_FreeChunk(m_sound);
}

void Sound::volume(float vol) {
    Mix_VolumeChunk(m_sound, vol * MIX_MAX_VOLUME);
}

void Sound::play(int channel, int loop) {
    Mix_PlayChannel(channel, m_sound, loop);
}

void Sound::play_fade(int time, int channel, int loop) {
    Mix_FadeInChannel(channel, m_sound, loop, time);
}

}