#include "Audio/Music.hpp"

namespace AMB {

float Music::s_volume = 1.0f;

Music::Music(const std::string& path) {
    // Load the music
    m_music = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!m_music) {
        Logger::instance().log(Error, "Can not load music. Music path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        exit(EXIT_FAILURE);
    }    
}

Music::~Music() {
    Mix_FreeMusic(m_music);
}

void Music::play(int32_t loop) const {
    if (m_music == nullptr) {
        Logger::instance().log(Error, "Music MIX not correctly loaded");
        return;
    }
    Mix_PlayMusic(m_music, loop);
}

void Music::play_fade(int32_t time_fade, int32_t loop) const {
    Mix_FadeInMusic(m_music, loop, time_fade);
}

void Music::volume(float vol) {
    s_volume = std::max(std::min(1.0f, vol), 0.0f);
    Mix_VolumeMusic(s_volume * MIX_MAX_VOLUME);
}

float Music::get_volume() {
    return s_volume;
}

void Music::pause() {
    Mix_PauseMusic();
}

void Music::resume() {
    Mix_ResumeMusic();
}

void Music::stop() {
    Mix_HaltMusic();
}

void Music::stop_fade(int32_t time) {
    Mix_FadeOutMusic(time);
}

bool Music::is_playing() {
    return Mix_PlayingMusic();
}

bool Music::is_paused() {
    return Mix_PausedMusic();
}

}