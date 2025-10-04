#pragma once

#include <string>
#include <glad/glad.h>

#include "Asset/AssetManager.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

namespace AMB {

class AssetFactory {
public:

    AssetFactory(AssetManager& manager);

    AssetHandle create_music(const std::string& path);

    AssetHandle create_sound(const std::string& path);

    AssetHandle create_shader(const std::string& vertex_path, const std::string& fragment_path);

private:
    AssetManager& m_manager;

    bool load_shader_source(const std::string path, std::string& source);

    bool create_shader_partial(GLenum type, uint32_t& shader_index, const std::string& source);

    bool create_shader_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);
};

}