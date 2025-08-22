#pragma once

#include <cstdint>
#include <string>
#include <Logger/Logger.hpp>
#include <SDL2/SDL_mixer.h>

namespace AMB {

class Audio {
public:
    Audio(int32_t mix_flags, int32_t frequency, uint16_t format, int32_t channels, int32_t chunk_size) {
        // Init MIX
        if (Mix_Init(mix_flags) != mix_flags) {
            std::string sdl_error(Mix_GetError());
            Mix_Quit();
            Logger::instance().log(Info, "Can not initialize MIX. Mix ERROR : " + sdl_error);
            exit(EXIT_FAILURE);
        }
        Logger::instance().log(Info, "MIX initialize");

        // Open Audio
        if (Mix_OpenAudio(frequency, format, channels, chunk_size) < 0) {
            std::string sdl_error(Mix_GetError());
            Mix_CloseAudio();
            Mix_Quit();
            Logger::instance().log(Info, "Can not open audio. Mix ERROR : " + sdl_error);
            exit(EXIT_FAILURE);
        }
        Logger::instance().log(Info, "Audio open");

        Logger::instance().log(Info, "Audio manager created");
    }

    ~Audio() {
        // Close audio and quit mix
        Mix_CloseAudio();
        Mix_Quit();

        Logger::instance().log(Info, "Audio manager destroyed");
    }

};

}