#include "Event/Mouse.hpp"

namespace AMB {

Mouse::Mouse() 
: m_window_height(0)
{
    m_button_state.fill(0);
}

bool Mouse::button_down(MouseButton button) const {
    return m_button_state[button] == 1;
}

bool Mouse::button_up(MouseButton button) const {
    return m_button_state[button] == 3;
}

bool Mouse::button_press(MouseButton button) const {
    return m_button_state[button] == 2 || m_button_state[button] == 1;
}

int32_t Mouse::mouse_x() const {
    return m_mouse_x;
}

int32_t Mouse::mouse_y() const {
    return m_mouse_y;
}

void Mouse::mouse_position(int32_t& x, int32_t& y) const {
    x = m_mouse_x;
    y = m_mouse_y;
}

void Mouse::manage() {
    SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
    m_mouse_y = m_window_height - m_mouse_y;

    for (auto& state : m_button_state) {

        // From down to press
        if (state == 1) {
            state = 2;

        // From up to nothing
        }else if(state == 3) {
            state = 0;
        }
    }
}

void Mouse::reset() {
    m_mouse_x = 0;
    m_mouse_y = 0;

    m_button_state.fill(0);
    m_button_state.fill(0);
}

void Mouse::manage_down(uint8_t button) {
    m_button_state[button] = 1;
}

void Mouse::manage_up(uint8_t button) {
    m_button_state[button] = 3;
}

void Mouse::set_window_height(int32_t height) {
    m_window_height = height;
}

}