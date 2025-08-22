#include "Time/Timer.hpp"

namespace AMB {

Timer::Timer(uint32_t fps)
: m_last_frame(std::chrono::high_resolution_clock::now())
{
    m_fps = fps;
    m_delta_time = 1000.0f/m_fps;

    Logger::instance().log(Info, "Timer created");
}

Timer::~Timer() {
    Logger::instance().log(Info, "Timer destroyed");
}

float Timer::get_delta_time() const {
    return m_delta_time;
}

uint32_t Timer::get_fps() const {
    return m_fps;
}

void Timer::set_fps(uint32_t fps) {
    m_fps = fps;
    m_delta_time = 1000.0f/m_fps;
}

void Timer::wait() {
    // Get current tick since the beginning of the application
    auto current_tick = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(current_tick - m_last_frame).count();

    // Wait for a given time
    if (elapsed_time < m_delta_time) {
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(m_delta_time - elapsed_time));
    }

    // Set the new frame time
    m_last_frame = current_tick;
}

}