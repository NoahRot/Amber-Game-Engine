#pragma once

namespace ora {

/// @brief Level of log and display modes
enum LogLevel {
    // Levels
    Fatal   = 0b00000001,
    Error   = 0b00000010,
    Warning = 0b00000100,
    Info    = 0b00001000,
    Debug   = 0b00010000,

    //Display modes
    DispCMD = 0b00100000,
    DispTXT = 0b01000000
};

}