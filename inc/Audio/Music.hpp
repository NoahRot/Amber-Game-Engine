#pragma once

#include <SDL2/SDL_mixer.h>

#include <algorithm>
#include <string>

#include <Logger/Logger.hpp>

namespace AMB {

class Music {
public:
    Music(Mix_Music* music);

    Music(const Music&) = delete; 
    Music& operator=(const Music&) = delete;

    ~Music();

    void play(int32_t loop = 0) const;

    void play_fade(int32_t time_fade, int32_t loop = 0) const;

    static void volume(float vol);

    static float get_volume();

    static void pause();

    static void resume();

    static void stop();

    static void stop_fade(int32_t time);

    static bool is_playing();

    static bool is_paused();

private:
    Mix_Music* m_music;

    static float s_volume;
};

}