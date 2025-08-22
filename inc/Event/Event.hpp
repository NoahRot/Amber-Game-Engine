#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Event/Keyboard.hpp"
#include "Event/Mouse.hpp"
#include "Logger/Logger.hpp"

#include "Window/Window.hpp"

namespace AMB {

class EventManager {
public:

    /// @brief Constructor
    /// @param window Pointer to the window of the application
    EventManager(Window* window);

    /// @brief Destructor
    ~EventManager();

    /// @brief Manage the event. 
    /// Should be call at the beginning of each loop.
    void manage();

    /// @brief reset everything. Put all state to 0.
    void reset();

    /// @brief To know if the application has been stopped
    /// @return True if the application has been stopped, False otherwise
    bool is_quitting() const;
    
    /// @brief Trigger the quit parameter. Quit the application.
    void quit();

    /// @brief Obtain the keyboard class
    /// @return A constant reference to the keyboard
    const Keyboard& keyboard() const;

    /// @brief Obtain the mouse class
    /// @return A constant reference to the mouse
    const Mouse& mouse() const;

private:

    /// @brief To know if the application has been stopped
    bool m_quit;

    /// @brief Keyboard of the application
    Keyboard m_keyboard;

    /// @brief Mouse of the application
    Mouse m_mouse;
};

}