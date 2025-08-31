# include "Configuration/Configuration.hpp"

namespace AMB {

Configuration& Configuration::instance() {
    static Configuration s_instance = Configuration();
    return s_instance;
}

void Configuration::initialize() {
    if (m_initialized) {
        std::cerr << "Configuration Warning: Configuration is already initialized." << std::endl;
        return;
    }

    m_initialized = true;
}

bool Configuration::is_initialized() {
    return m_initialized;
}

Hierarchy Configuration::config_to_hierarchy() const {
    Hierarchy hierarchy;
    hierarchy.name = "Configuration";

    // Logger parameters
    add_data(hierarchy["Logger"], "file_name", log_file_name);
    add_data(hierarchy["Logger"], "state", log_state);

    // Window parameters
    add_data(hierarchy["Window"], "width", win_width);
    add_data(hierarchy["Window"], "height", win_height);
    add_data(hierarchy["Window"], "title", win_title);
    add_data(hierarchy["Window"], "sdl_flags", win_sdl_flags);
    add_data(hierarchy["Window"], "win_flags", win_win_flags);

    // Timer parameter
    add_data(hierarchy["Timer"], "fps", tim_fps);

    // Audio parameters
    add_data(hierarchy["Audio"], "mix_flags", aud_mix_flags);
    add_data(hierarchy["Audio"], "frequency", aud_frequency);
    add_data(hierarchy["Audio"], "format", aud_format);
    add_data(hierarchy["Audio"], "channels", aud_channels);
    add_data(hierarchy["Audio"], "chunksize", aud_chunksize);

    return hierarchy;
}

bool Configuration::load_configuration(const std::string& path) {
    Serializer serializer;
    Hierarchy hierarchy;
    if (!serializer.deserialize_bin(hierarchy, path)) {
        Logger::instance().log(Error, "No configuration file found");
        return false;
    }

    // Logger parameters
    get_data(hierarchy["Logger"], "file_name", log_file_name);
    get_data(hierarchy["Logger"], "state", log_state);

    // Window parameters
    get_data(hierarchy["Window"], "width", win_width);
    get_data(hierarchy["Window"], "height", win_height);
    get_data(hierarchy["Window"], "title", win_title);
    get_data(hierarchy["Window"], "sdl_flags", win_sdl_flags);
    get_data(hierarchy["Window"], "win_flags", win_win_flags);

    // Timer parameter
    get_data(hierarchy["Timer"], "fps", tim_fps);

    // Audio parameters
    get_data(hierarchy["Audio"], "mix_flags", aud_mix_flags);
    get_data(hierarchy["Audio"], "frequency", aud_frequency);
    get_data(hierarchy["Audio"], "format", aud_format);
    get_data(hierarchy["Audio"], "channels", aud_channels);
    get_data(hierarchy["Audio"], "chunksize", aud_chunksize);

    return true;
}

bool Configuration::save_configuration(const std::string& path) const {

    Hierarchy hierarchy = config_to_hierarchy();

    Serializer serializer;
    return serializer.serialize_bin(hierarchy, path);
}

std::string Configuration::get_log_file_name() const {
    return log_file_name;
}

void Configuration::set_log_file_name(const std::string& name) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change log file name after initialization.");
        return;
    }
    log_file_name = name;
}

uint8_t Configuration::get_log_state() const {
    return log_state;
}

void Configuration::set_log_state(uint8_t state) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change log state before initialization.");
        return;
    }
    log_state = state;
}

uint32_t Configuration::get_win_width() const {
    return win_width;
}

void Configuration::set_win_width(uint32_t width) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change window width after initialization.");
        return;
    }
    win_width = width;
}

uint32_t Configuration::get_win_height() const {
    return win_height;
}

void Configuration::set_win_height(uint32_t height) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change window height after initialization.");
        return;
    }
    win_height = height;
}

std::string Configuration::get_win_title() const {
    return win_title;
}

void Configuration::set_win_title(const std::string& title) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change window title after initialization.");
        return;
    }
    win_title = title;
}

uint32_t Configuration::get_win_sdl_flags() const {
    return win_sdl_flags;
}

void Configuration::set_win_sdl_flags(uint32_t flags) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change SDL flags after initialization.");
        return;
    }
    win_sdl_flags = flags;
}

uint32_t Configuration::get_win_win_flags() const {
    return win_win_flags;
}

void Configuration::set_win_win_flags(uint32_t flags) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change window flags after initialization.");
        return;
    }
    win_win_flags = flags;
}

uint32_t Configuration::get_tim_fps() const {
    return tim_fps;
}

void Configuration::set_tim_fps(uint32_t fps) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change timer FPS after initialization.");
        return;
    }
    tim_fps = fps;
}

int32_t Configuration::get_aud_mix_flags() const {
    return aud_mix_flags;
}

void Configuration::set_aud_mix_flags(int32_t flags) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change audio mix flags after initialization.");
        return;
    }
    aud_mix_flags = flags;
}

int32_t Configuration::get_aud_frequency() const {
    return aud_frequency;
}

void Configuration::set_aud_frequency(int32_t frequency) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change audio frequency after initialization.");
        return;
    }
    aud_frequency = frequency;
}

uint16_t Configuration::get_aud_format() const {
    return aud_format;
}

void Configuration::set_aud_format(uint16_t format) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change audio format after initialization.");
        return;
    }
    aud_format = format;
}

int32_t Configuration::get_aud_channels() const {
    return aud_channels;
}

void Configuration::set_aud_channels(int32_t channels) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change audio channels after initialization.");
        return;
    }
    aud_channels = channels;
}

int32_t Configuration::get_aud_chunksize() const {
    return aud_chunksize;
}

void Configuration::set_aud_chunksize(int32_t chunksize) {
    if (m_initialized) {
        Logger::instance().log(AMB::Error, "Cannot change audio chunk size after initialization.");
        return;
    }
    aud_chunksize = chunksize;
}

Configuration::Configuration()
:   log_file_name("UNKNOWN.log"), log_state(0b11111111),
    win_width(1920), win_height(1080), win_title("AMBER Engine"),
    win_sdl_flags(SDL_INIT_EVERYTHING), win_win_flags(SDL_WINDOW_OPENGL),
    tim_fps(60),
    aud_mix_flags(MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MID|MIX_INIT_OPUS),
    aud_frequency(22050), aud_format(0x8010), aud_channels(2), aud_chunksize(1024)
{}

}