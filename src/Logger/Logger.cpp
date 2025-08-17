#include "Logger/Logger.hpp"

ora::LogState ora::Logger::s_state = 0b11111111;
std::string ora::Logger::s_log_file_path = "UNKNOWN.log";

namespace ora {

void _log_callback(LogLevel level, const std::string& message, bool cmd, bool txt, std::ofstream& stream) {
    // Create log string and take the time of the log
    std::string log_lvl;
    std::string color_lvl;

    // Add the level of the log and color
    switch (level)
    {
    case Fatal:
        log_lvl = "FATAL";
        color_lvl = "\033[91m";
        break;
    case Error:
        log_lvl = "ERROR";
        color_lvl = "\033[93m";
        break;
    case Warning:
        log_lvl = "WARNING";
        color_lvl = "\033[95m";
        break;
    case Info:
        log_lvl = "INFO";
        color_lvl = "\033[94m";
        break;
    case Debug:
        log_lvl = "DEBUG";
        color_lvl = "\033[92m";
        break;
    default:
        log_lvl = "UNKNOWN";
        color_lvl = "\033[97m";
        break;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream time_str;
    time_str << std::put_time(std::localtime(&time), "%H:%M:%S");
    
    // CMD Display
    if (cmd) {
        std::cout << "\033[90m[" << time_str.str() << "] " << color_lvl << log_lvl << "\033[37m : " << message << "\033[0m" << std::endl;
    }
    
    // Txt Display
    if (txt) {
        stream << "[" << time_str.str() << "] " << log_lvl << " : " << message << "\n";
    }
}

Logger::Logger(const std::string& log_file_path, LogState state)
: m_state(state)
{
    m_log_file = std::make_unique<std::ofstream>();
    m_log_file->open(log_file_path);

    if (!m_log_file->is_open()) {
        set_display_txt(false);

        log(Error, "Logger can not open log file. Log file path : " + log_file_path);
    }

    log(ora::Info, "Logger created");
}

Logger::~Logger() {
    log(ora::Info, "Logger destroyed");

    if (m_log_file && m_log_file->is_open()) {
        m_log_file->close();
    }
}

void Logger::init(LogState state, const std::string& log_file_path) {
    s_state = state;
    s_log_file_path = log_file_path;
}

Logger& Logger::instance() {
    static Logger s_instance = Logger(s_log_file_path, s_state);
    return s_instance;
}

void Logger::set_display_cmd(bool state) {
    m_state = (m_state & ~(DispCMD)) | (DispCMD*state);
}

void Logger::set_display_txt(bool state) {
    if (state && !m_log_file->is_open()){
        std::cerr << "Logger Error : Logger file has not been open, thus can not write in it." << std::endl;
        return;
    }
    m_state = (m_state & ~(DispTXT)) | (DispTXT*state);
}

void Logger::set_level(LogLevel level, bool state) {
    if (state && (level & DispTXT) == DispTXT && !m_log_file->is_open()){
        log(Error, "Logger file has not been open, thus can not write in it.");
        return;
    }
    m_state = (m_state & ~(level)) | (level*state);
}

bool Logger::is_display(LogLevel level) {
    return (m_state & level) == level;
}

LogState Logger::get_state() const {
    return m_state;
}

void Logger::log(LogLevel level, const std::string& message) const {
    if ((m_state &  level) == level){
        _log_callback(level, message, (m_state & DispCMD) == DispCMD, (m_state & DispTXT) == DispTXT, *m_log_file);
    }
}

Logger& _init_logger(LogState state, const std::string& log_file_path) {
    Logger::init(state, log_file_path);
    return Logger::instance();
}

}