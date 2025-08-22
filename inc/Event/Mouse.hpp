#pragma once

#include <array>

#include <SDL2/SDL.h>

#include "Event/MouseButton.hpp"

namespace AMB {

class Mouse {
public:
    Mouse();

    bool button_down(MouseButton button) const;

    bool button_up(MouseButton button) const;

    bool button_press(MouseButton button) const;

    int32_t mouse_x() const;

    int32_t mouse_y() const;

    void mouse_position(int32_t& x, int32_t& y) const;

    void manage();

    void reset();

    void manage_down(uint8_t button);

    void manage_up(uint8_t button);

    void set_window_height(int32_t height);

private:

    // Button state 0 = nothing, 1 = down, 2 = pressed, 3 = up
    std::array<uint8_t, MOUSE_BUTTON_COUNT> m_button_state;

    int32_t m_mouse_x;
    int32_t m_mouse_y;

    int32_t m_window_height;
};

}