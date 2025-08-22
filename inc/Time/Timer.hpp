#pragma once

#include <inttypes.h>
#include <iostream>
#include <chrono>
#include <thread>

#include <SDL2/SDL.h>

#include "Logger/Logger.hpp"

namespace AMB {

class Timer {
public:
    /// @brief Constructor
    Timer(uint32_t fps);

    /// @brief Destructor
    ~Timer();

    /// @brief Get the time for each frame in millisecond
    /// @return The number of millisecond per frame
    float get_delta_time() const;

    /// @brief Get the FPS of the application
    /// @return The FPS
    uint32_t get_fps() const;

    /// @brief Change the FPS of the application
    /// @param fps The new FPS
    void set_fps(uint32_t fps);

    /// @brief A method to call at each frame. Wait until the next frame.
    void wait();

private:
    /// @brief The FPS of the application
    uint32_t m_fps;

    /// @brief The time per frame in millisecond
    float m_delta_time;

    /// @brief The last frame time (in millisecond since the start of the application)
    std::chrono::time_point<std::chrono::high_resolution_clock> m_last_frame;
};

}