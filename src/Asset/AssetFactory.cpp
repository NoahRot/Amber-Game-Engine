#include "Asset/AssetFactory.hpp"

// Using stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "External/stb_image/stb_image_write.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace AMB {

AssetFactory::AssetFactory(AssetManager& manager, FontSystem& font_system)
: m_manager(manager), m_font_system(font_system)
{}

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

AssetHandle AssetFactory::create_texture(const std::string& path) {
    // Read the file from top to bottom
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    int width(-1), height(-1), bpp;
    unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4); // 4 because RGBA

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Check if the buffer contains data
    if (buffer) {
        stbi_image_free(buffer);
    }else{
        Logger::instance().log(Error, "Can't load texture : " + path);
        glDeleteTextures(1, &texture_index);
        return AssetHandle{-1, typeid(Texture)};
    }

    return m_manager.textures.add(texture_index, width, height, bpp);
}

AssetHandle AssetFactory::create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    std::vector<std::array<unsigned char, 4>> data(width * height, std::array<unsigned char,4>{r, g, b, a});

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    return m_manager.textures.add(texture_index, width, height, 4);
}

AssetHandle AssetFactory::create_texture_from_data(int32_t width, int32_t height, uint32_t format_store, uint32_t format_load, uint32_t data_type, void* data) {
    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, format_store, width, height, 0, format_load, data_type, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return m_manager.textures.add(texture_index, width, height, 4);
}

AssetHandle AssetFactory::create_font(const std::string& path, uint32_t font_size) {
    // Get logger
    const Logger& logger = Logger::instance();

    // Get font face
    FT_Face face;
    if (FT_New_Face(m_font_system.get_library(), path.c_str(), 0, &face)) {
        logger.log(Error, "Can not load font : " + path);
        return AssetHandle{-1, typeid(Font)};
    }

    // Set font size
    FT_Set_Pixel_Sizes(face, 0, font_size);

    // Prepare byte size unpacking
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create the characters
    std::map<char, Character> char_map;
    int char_px_space = Font::get_char_px_space();
    int atlas_width(0);
    int atlas_height(0);

    for (unsigned char c(32) ; c < 128 ; ++c) {

        // Load a character
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {    // Check validity
            logger.log(Error, "FreeType Failed to load Glyph : " + c);

        }else{                                          // Create Character
            Character character = {
                0.0f, 0.0f, 0.0f, 0.0f, 
                (int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows,
                face->glyph->bitmap_left, face->glyph->bitmap_top,
                face->glyph->advance.x
            };

            char_map[c] = character;                    // Set the character in the map

            // Update atlas parameters
            atlas_width += character.width;
            if (c < 128) {
                atlas_width += char_px_space;
            }
            atlas_height = std::max(atlas_height, character.height);
        }
    }

    // Create the font texture atlas
    AssetHandle texture_font_handle = create_texture(atlas_width, atlas_height, 0, 0, 0, 0);
    if (!m_manager.textures.validity(texture_font_handle)) {
        FT_Done_Face(face);
        logger.log(Error, "Can not create texture for font");
        return AssetHandle{-1, typeid(Font)};
    }
    Texture& texture = m_manager.textures.get(texture_font_handle);

    // Populate the texture with the characters
    texture.bind();
    int x_progression(0);
    for (auto& c : char_map) {
        FT_Load_Char(face, c.first, FT_LOAD_RENDER);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x_progression, 0, c.second.width, c.second.height, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas_width, atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

        // Set the position and dimension on the texture atlas
        c.second.u = x_progression/(float)atlas_width;
        c.second.w = c.second.width/(float)atlas_width;
        c.second.h = c.second.height/(float)atlas_height;

        // Progress
        x_progression += c.second.width + char_px_space;
    }

    // Free face
    FT_Done_Face(face);

    // Create the font
    return m_manager.fonts.add(char_map, atlas_height, texture);
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