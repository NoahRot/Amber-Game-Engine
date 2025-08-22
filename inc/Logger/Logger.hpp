#pragma once

#include <inttypes.h>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>

#include "Logger/LogLevel.hpp"

namespace AMB {

/// @brief State of the log class
typedef uint8_t LogState;

/// @brief Callback function for log. Can be use for multithreading.
/// @param level Level of log
/// @param message Message of log
/// @param cmd Are we log in CMD
/// @param txt Are we log in texte log file
/// @param stream Log file
void _log_callback(LogLevel level, const std::string& message, bool cmd, bool txt, std::ofstream& stream);

/// @brief Logger class
/// Singleton class to log content
class Logger {
public:

    static void init(LogState state, const std::string& log_file_path);

    static Logger& instance();

    /// @brief Set display in CMD
    /// @param state True for display in CMD
    void set_display_cmd(bool state);

    /// @brief Set display in log file
    /// @param state True for display in log file
    void set_display_txt(bool state);

    /// @brief Set display level of log
    /// @param level The level of log to set
    /// @param state True for display, false otherwise
    void set_level(LogLevel level, bool state);

    /// @brief Is the given level/display mode enable
    /// @param level Level of log or display mode
    /// @return True if enable, false otherwise
    bool is_display(LogLevel level);

    /// @brief Get the state of the log class
    /// @return The state of the log class
    LogState get_state() const;

    /// @brief Log a message
    /// @param level Level of the log
    /// @param message Message of the log
    void log(LogLevel level, const std::string& message) const;

private:

    /// @brief Constructor
    /// @param state State of the log class
    /// @param log_file_path Path to the log file
    Logger(const std::string& log_file_path, LogState state = 0b11111111);

    /// @brief Destructor
    ~Logger();

    Logger(const Logger&) = delete;             // Deleted because singleton

    Logger operator=(const Logger&) = delete;   // Deleted because singleton

    /// @brief Current state of the log class
    LogState m_state;

    /// @brief Log file
    std::unique_ptr<std::ofstream> m_log_file;

    /// @brief Static State. It can be change before initializing the Logger.
    /// Once the logger is created, it will use its own m_state 
    static LogState s_state;

    /// @brief Path the the log file.
    static std::string s_log_file_path;
};

/// @brief Initialize Logger
/// @param state The state of the logger. What to display and how.
/// @param log_file_path The log file.
/// @return A constant reference to the logger
Logger& _init_logger(LogState state, const std::string& log_file_path);

}