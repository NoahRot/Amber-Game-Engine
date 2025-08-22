#pragma once

#include <SDL2/SDL_mixer.h>

#include <algorithm>
#include <string>

#include <Logger/Logger.hpp>

namespace AMB {

class Sound {
public:
    Sound(const std::string& path);

    Sound(const Sound&) = delete; 
    Sound& operator=(const Sound&) = delete;

    ~Sound();

    void volume(float vol);

    void play(int channel = -1, int loop = 0);

    void play_fade(int time, int channel = -1, int loop = 0);

private:
    Mix_Chunk* m_sound;

    float m_volume;
};

}