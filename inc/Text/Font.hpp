#pragma once

#include <map>

#include "Text/Character.hpp"
#include "Graphic/Texture.hpp"
#include "Asset/AssetHandle.hpp"
#include "Logger/Logger.hpp"

namespace AMB {

class Font {
public:
    Font(const std::map<char, Character>& char_map, uint32_t height, Texture& texture);

    ~Font();

    Character get_char(char c);

    int32_t get_height() const;

    Texture& get_texture() const;

    static uint32_t get_char_px_space();

private:
    std::map<char, Character> m_char_map;
    uint32_t m_height;
    Texture& m_texture;

    constexpr static uint32_t CHAR_PX_SPACE = 2;
};

}