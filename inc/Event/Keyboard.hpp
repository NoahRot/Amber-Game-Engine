#pragma once

#include <array>
#include <vector>

#include <SDL2/SDL.h>

#include "Event/KeyCode.hpp"

namespace AMB {

class Keyboard {
public:

    /// @brief Constructor
    Keyboard();

    /// @brief To know if a key is down
    /// @param code Code of the key
    /// @return True if the key is down
    bool key_down(KeyCode code) const;

    /// @brief To know if a key is up
    /// @param code Code of the key
    /// @return True if the key is up
    bool key_up(KeyCode code) const;

    /// @brief To know if a key is pressed
    /// @param code Code of the key
    /// @return True if the key is pressed
    bool key_press(KeyCode code) const;

    /// @brief Manage the keyboard event
    void manage();

    /// @brief Reset the keyboard. Everything put at 0.
    void reset();

    /// @brief A key has been pressed
    /// @param code Code of the key
    void manage_down(KeyCode code);

    /// @brief A key has been released
    /// @param code Code of the key
    void manage_up(KeyCode code);

    const std::vector<char>& get_buffer() const { return m_buffer; }

private:

    // Key state 0 = nothing, 1 = down, 2 = pressed, 3 = up
    std::array<uint8_t, KEY_NUM_CODES> m_key_state;
    
    std::vector<char> m_buffer;
};

}