#pragma once

#include <string>
#include <inttypes.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Logger/Logger.hpp"
#include "Serialization/Serializer.hpp"

namespace AMB {

class Configuration {
public:
    static Configuration& instance();

    void initialize();

    bool is_initialized();

    Hierarchy config_to_hierarchy() const;

    bool load_configuration(const std::string& path);
    
    bool save_configuration(const std::string& path) const;

    std::string get_log_file_name() const;

    void set_log_file_name(const std::string& name);

    uint8_t get_log_state() const;

    void set_log_state(uint8_t state);

    uint32_t get_win_width() const;

    void set_win_width(uint32_t width);

    uint32_t get_win_height() const;

    void set_win_height(uint32_t height);

    std::string get_win_title() const;

    void set_win_title(const std::string& title);

    uint32_t get_win_sdl_flags() const;

    void set_win_sdl_flags(uint32_t flags);

    uint32_t get_win_win_flags() const;

    void set_win_win_flags(uint32_t flags);

    uint32_t get_tim_fps() const;

    void set_tim_fps(uint32_t fps);

    int32_t get_aud_mix_flags() const;

    void set_aud_mix_flags(int32_t flags);

    int32_t get_aud_frequency() const;

    void set_aud_frequency(int32_t frequency);

    uint16_t get_aud_format() const;

    void set_aud_format(uint16_t format);

    int32_t get_aud_channels() const;

    void set_aud_channels(int32_t channels);

    int32_t get_aud_chunksize() const;

    void set_aud_chunksize(int32_t chunksize);
    
private:
    Configuration();

    ~Configuration() = default;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    bool m_initialized;

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