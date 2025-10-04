#include "Asset/AssetFactory.hpp"

namespace AMB {

AssetFactory::AssetFactory(AssetManager& manager)
: m_manager(manager) {}

AssetHandle AssetFactory::create_music(const std::string& path) {
    // Load the music
    Mix_Music* music = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!music) {
        Logger::instance().log(Error, "Can not load music. Music path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        exit(EXIT_FAILURE);
    }  
    
    return m_manager.musics.add(music);
}

AssetHandle AssetFactory::create_sound(const std::string& path) {
    // Load the sound
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

    // Check if the sound has been loaded successfully
    if (!sound) {
        Logger::instance().log(Error, "Can not load sound. Sound path : " + path + ". Mix Error : " + std::string(Mix_GetError()));
        exit(EXIT_FAILURE);
    }

    return m_manager.sounds.add(sound);
}

AssetHandle AssetFactory::create_shader(const std::string& vertex_path, const std::string& fragment_path) {
    // Load shaders source code
    std::string vertex_source_code;
    std::string fragment_source_code;
    AssetHandle handle{-1, typeid(Shader)};

    if (!load_shader_source(fragment_path, fragment_source_code)) {
        return handle;
    }
    if (!load_shader_source(vertex_path, vertex_source_code)) {
        return handle;
    }

    // Create shaders
    uint32_t vertex_shader;
    uint32_t fragment_shader;

    if (!create_shader_partial(GL_VERTEX_SHADER, vertex_shader, vertex_source_code)) {
        glDeleteShader(vertex_shader);
        return handle;
    }

    if (!create_shader_partial(GL_FRAGMENT_SHADER, fragment_shader, fragment_source_code)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return handle;
    }

    // Create shader program
    uint32_t shader_program;
    if (!create_shader_program(vertex_shader, fragment_shader, shader_program)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return handle;
    }

    // Delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return m_manager.shaders.add(shader_program);
}


bool AssetFactory::load_shader_source(const std::string path, std::string& source) {
    // Open file
    std::fstream shader_file;
    shader_file.open(path);
    if (shader_file.fail()) {
        Logger::instance().log(Error, "Can not load shader source. Shader path : " + path);
        return false;
    }

    // Load the source file
    std::stringstream stream;
    stream << shader_file.rdbuf();
    source = stream.str();

    // Close file
    shader_file.close();

    return true;
}

bool AssetFactory::create_shader_partial(GLenum type, uint32_t& shader_index, const std::string& source) {
    // Define error variable
    int success;
    char info_log[512];

    // Compile the shader
    shader_index = glCreateShader(type);
    const char* sourceChar = source.c_str();
    glShaderSource(shader_index, 1, &sourceChar, nullptr);
    glCompileShader(shader_index);

    // Check for errors
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, info_log);
        std::string shader_type_str;
        switch (type) {
            case GL_VERTEX_SHADER:
                shader_type_str = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                shader_type_str = "fragment";
                break;
            default:
                break;
        }
        Logger::instance().log(Error, "Can not compile " + shader_type_str + " shader. Error :\n" + std::string(info_log));
        return false;
    }

    return true;
}

bool AssetFactory::create_shader_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program) {
    // Define error variable
    int success;
    char info_log[512];

    // Create shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    // Check for errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        Logger::instance().log(Info, "Can not bind shader to shader program. Error :\n" + std::string(info_log));
        return false;
    }

    return true;
}

}