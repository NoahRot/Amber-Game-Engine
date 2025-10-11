#pragma once

#include <map>

#include "Text/Character.hpp"
#include "Graphic/Texture.hpp"
#include "Asset/AssetHandle.hpp"
#include "Logger/Logger.hpp"

namespace AMB {

class Font {
public:
    Font(const std::map<char, Character>& char_map, uint32_t height, Texture& texture)
    : m_char_map(char_map), m_height(height), m_texture(texture) {}

    ~Font() {}

    Character get_char(char c) {
        return m_char_map[c];
    }

    int32_t get_height() const {
        return m_height;
    }

    Texture& get_texture() const {
        return m_texture;
    }

    static uint32_t get_char_px_space() {
        return CHAR_PX_SPACE;
    }

private:
    std::map<char, Character> m_char_map;
    uint32_t m_height;
    Texture& m_texture;

    constexpr static uint32_t CHAR_PX_SPACE = 2;
};

}