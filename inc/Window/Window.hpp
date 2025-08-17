#pragma once

#include <inttypes.h>
#include <string>

#include <SDL2/SDL.h>
#include <External/glad/glad.h>

#include "Logger/Logger.hpp"

namespace ora {

/// @brief Window class
class Window {
public:

    /// @brief Constructor
    /// @param width Width of the window
    /// @param height Height of the window
    /// @param title Title of the window
    /// @param sdl_flags SDL flags
    /// @param win_flags SDL window flags
    Window(uint32_t width, uint32_t height, std::string title, uint32_t sdl_flags, uint32_t win_flags);

    /// @brief Destructor
    ~Window();

    /// @brief Get the width of the window
    /// @return The width of the window
    uint32_t get_width() const;

    /// @brief Get the height of the window
    /// @return The height of the window
    uint32_t get_height() const;

    /// @brief Swap window buffer. Present the new frame.
    void present() const;

private:
    /// @brief Width of the window
    uint32_t m_width;

    /// @brief Height of the window
    uint32_t m_height;

    /// @brief Title of the window
    std::string m_title;

    /// @brief SDL window pointer, window of the application
    SDL_Window* m_window;

    /// @brief OpenGL Context
    SDL_GLContext m_context;
};

}