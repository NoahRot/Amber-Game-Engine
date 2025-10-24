#include "Sprite/SpriteSheet.hpp"

namespace AMB {

SpriteSheet::SpriteSheet(AssetHandle texture_handle)
: m_texture_handle(texture_handle)
{}

uint32_t SpriteSheet::add_sprite(mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim) {
    m_sprites.push_back(Sprite(m_texture_handle, position, dimension, texture_coord, texture_dim));
    return m_sprites.size() - 1;
}

Sprite SpriteSheet::get_sprite(uint32_t id) {
    return m_sprites.at(id);
}

bool SpriteSheet::validity(uint32_t id) const {
    return id < m_sprites.size();
}

uint32_t SpriteSheet::size() const {
    return m_sprites.size();
}

}