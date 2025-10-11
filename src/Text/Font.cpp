#include "Text/Font.hpp"

namespace AMB {

Font::Font(const std::map<char, Character>& char_map, uint32_t height, Texture& texture)
: m_char_map(char_map), m_height(height), m_texture(texture) {}

Font::~Font() {}

Character Font::get_char(char c) {
    return m_char_map[c];
}

int32_t Font::get_height() const {
    return m_height;
}

Texture& Font::get_texture() const {
    return m_texture;
}

uint32_t Font::get_char_px_space() {
    return CHAR_PX_SPACE;
}

}