#pragma once

#include <string>
#include <glad/glad.h>

#include "External/stb_image/stb_image_write.h"

#include "Asset/AssetManager.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

#include "Text/Font.hpp"
#include "Text/FontSystem.hpp"

namespace AMB {

class AssetFactory {
public:

    AssetFactory(AssetManager& manager, FontSystem& font_system);

    AssetHandle create_music(const std::string& path);

    AssetHandle create_sound(const std::string& path);

    AssetHandle create_shader(const std::string& vertex_path, const std::string& fragment_path);

    AssetHandle create_texture(const std::string& path);

    AssetHandle create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    
    AssetHandle create_texture_from_data(int32_t width, int32_t height, uint32_t format_store, uint32_t format_load, uint32_t data_type, void* data);

    AssetHandle create_font(const std::string& path, uint32_t font_size);

private:
    AssetManager& m_manager;

    FontSystem& m_font_system;

    bool load_shader_source(const std::string path, std::string& source);

    bool create_shader_partial(GLenum type, uint32_t& shader_index, const std::string& source);

    bool create_shader_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);
};

}