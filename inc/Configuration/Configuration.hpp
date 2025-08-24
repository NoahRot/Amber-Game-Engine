#pragma once

#include <string>
#include <inttypes.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Logger/Logger.hpp"

namespace AMB {

class Configuration {
public:
    static Configuration& instance() {
        if (!s_initialized){
            Logger::instance().log(AMB::Fatal, "Configuration is not initialized. Call Configuration::initialize() before accessing the instance.");
            exit(EXIT_FAILURE);
        }
        static Configuration s_instance = Configuration();
        return s_instance;
    }

    static void initialize() {
        if (s_initialized) {
            std::cerr << "Configuration Warning: Configuration is already initialized." << std::endl;
            return;
        }

        s_initialized = true;
    }

    static bool is_initialized() {
        return s_initialized;
    }

    static bool load_configuration();
    
    void save_configuration() const;

    std::string get_log_file_name() const {
        return log_file_name;
    }

    void set_log_file_name(const std::string& name) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change log file name after initialization.");
            return;
        }
        log_file_name = name;
    }

    uint8_t get_log_state() const {
        return log_state;
    }

    void set_log_state(uint8_t state) {
        if (!s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change log state before initialization.");
            return;
        }
        log_state = state;
    }

    uint32_t get_win_width() const {
        return win_width;
    }

    void set_win_width(uint32_t width) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change window width after initialization.");
            return;
        }
        win_width = width;
    }

    uint32_t get_win_height() const {
        return win_height;
    }

    void set_win_height(uint32_t height) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change window height after initialization.");
            return;
        }
        win_height = height;
    }

    std::string get_win_title() const {
        return win_title;
    }

    void set_win_title(const std::string& title) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change window title after initialization.");
            return;
        }
        win_title = title;
    }

    uint32_t get_win_sdl_flags() const {
        return win_sdl_flags;
    }

    void set_win_sdl_flags(uint32_t flags) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change SDL flags after initialization.");
            return;
        }
        win_sdl_flags = flags;
    }

    uint32_t get_win_win_flags() const {
        return win_win_flags;
    }

    void set_win_win_flags(uint32_t flags) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change window flags after initialization.");
            return;
        }
        win_win_flags = flags;
    }

    uint32_t get_tim_fps() const {
        return tim_fps;
    }

    void set_tim_fps(uint32_t fps) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change timer FPS after initialization.");
            return;
        }
        tim_fps = fps;
    }

    int32_t get_aud_mix_flags() const {
        return aud_mix_flags;
    }

    void set_aud_mix_flags(int32_t flags) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change audio mix flags after initialization.");
            return;
        }
        aud_mix_flags = flags;
    }

    int32_t get_aud_frequency() const {
        return aud_frequency;
    }

    void set_aud_frequency(int32_t frequency) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change audio frequency after initialization.");
            return;
        }
        aud_frequency = frequency;
    }

    uint16_t get_aud_format() const {
        return aud_format;
    }

    void set_aud_format(uint16_t format) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change audio format after initialization.");
            return;
        }
        aud_format = format;
    }

    int32_t get_aud_channels() const {
        return aud_channels;
    }

    void set_aud_channels(int32_t channels) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change audio channels after initialization.");
            return;
        }
        aud_channels = channels;
    }

    int32_t get_aud_chunksize() const {
        return aud_chunksize;
    }

    void set_aud_chunksize(int32_t chunksize) {
        if (s_initialized) {
            Logger::instance().log(AMB::Error, "Cannot change audio chunk size after initialization.");
            return;
        }
        aud_chunksize = chunksize;
    }
    
private:
    Configuration()
    :   log_file_name("UNKNOWN.log"), log_state(0b11111111),
        win_width(1920), win_height(1080), win_title("AMBER Engine"),
        win_sdl_flags(SDL_INIT_EVERYTHING), win_win_flags(SDL_WINDOW_OPENGL),
        tim_fps(60),
        aud_mix_flags(MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MID|MIX_INIT_OPUS),
        aud_frequency(22050), aud_format(0x8010), aud_channels(2), aud_chunksize(1024)
    {}

    ~Configuration() = default;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    static bool s_initialized;

    // Logger parameters

    std::string log_file_name;
    uint8_t     log_state;

    // Window parameters

    uint32_t win_width;
    uint32_t win_height;
    std::string win_title;
    uint32_t win_sdl_flags;
    uint32_t win_win_flags;

    // Timer parameter

    uint32_t tim_fps;

    // Audio parameters

    int32_t aud_mix_flags;
    int32_t aud_frequency;
    uint16_t aud_format;
    int32_t aud_channels;
    int32_t aud_chunksize;

};

}