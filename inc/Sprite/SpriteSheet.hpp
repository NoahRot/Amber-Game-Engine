#pragma once

#include "Asset/AssetHandle.hpp"
#include "Sprite/Sprite.hpp"

namespace AMB {

class SpriteSheet {
public:
    SpriteSheet(AssetHandle texture_handle);

    uint32_t add_sprite(mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim);

    Sprite get_sprite(uint32_t id);

    bool validity(uint32_t id) const;

    uint32_t size() const;

private:
    AssetHandle m_texture_handle;
    std::vector<Sprite> m_sprites;
};

}