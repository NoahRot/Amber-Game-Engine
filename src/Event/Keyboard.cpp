#include "Event/Keyboard.hpp"

#include <iostream>

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
    m_buffer.clear();
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
    if (code >= KEY_CODE_A && code <= KEY_CODE_Z){
        if (key_press(KeyCode::KEY_CODE_LSHIFT) || key_press(KeyCode::KEY_CODE_RSHIFT)){
            m_buffer.push_back('A' + (code - KEY_CODE_A));  // 4 → 'A', 5 → 'B', ..., 29 → 'Z'
        }else {
            m_buffer.push_back('a' + (code - KEY_CODE_A));  // 4 → 'A', 5 → 'B', ..., 29 → 'Z'
        }
    }else if (code >= KEY_CODE_1 && code <= KEY_CODE_0){
        if (code == KEY_CODE_0) {
            m_buffer.push_back('0');
        }else{
            m_buffer.push_back('1' + (code - KEY_CODE_1));  // 30 → '1', 31 → '2', ..., 39 → '0'
        }
    }else if (code == KEY_CODE_BACKSPACE) {
        m_buffer.push_back('~'); // Backslash (placeholder)
    }
    
    m_key_state[code] = 1;
}

void Keyboard::manage_up(KeyCode code) {
    m_key_state[code] = 3;
}

}