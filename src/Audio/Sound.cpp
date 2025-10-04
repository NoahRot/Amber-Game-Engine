#include "Audio/Sound.hpp"

namespace AMB {

Sound::Sound(Mix_Chunk* sound) 
: m_sound(sound), m_volume(1.0f)
{
    

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