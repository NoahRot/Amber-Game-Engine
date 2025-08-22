#include "Event/Keyboard.hpp"

namespace AMB {

Keyboard::Keyboard() {
    m_key_state.fill(0);
}

bool Keyboard::key_down(KeyCode code) const {
    return m_key_state[code] == 1;
}

bool Keyboard::key_up(KeyCode code) const {
    return m_key_state[code] == 3;
}

bool Keyboard::key_press(KeyCode code) const {
    return m_key_state[code] == 2 || m_key_state[code] == 1;
}

void Keyboard::manage() {
    for (auto& state : m_key_state) {

        // From down to press
        if (state == 1) {
            state = 2;

        // From up to nothing
        }else if(state == 3) {
            state = 0;
        }
    }
}

void Keyboard::reset() {
    m_key_state.fill(0);
}

void Keyboard::manage_down(KeyCode code) {
    m_key_state[code] = 1;
}

void Keyboard::manage_up(KeyCode code) {
    m_key_state[code] = 3;
}

}