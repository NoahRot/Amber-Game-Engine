#pragma once

#include "Asset/AssetManager.hpp"
#include "Sprite/Sprite.hpp"
#include "Sprite/SpriteSheet.hpp"
#include "Sprite/SpriteAnimation.hpp"

namespace AMB {

class SpriteFactory {
public:
    SpriteFactory(AssetManager& asset_manager);

    Sprite create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f uv_coord, mat::Vec2f uv_dim);

    Sprite create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension);

    SpriteSheet create_sprite_sheet_quad(AssetHandle texture_handle, mat::Vec2i quad_dim, mat::Vec2f sprite_dim);

    SpriteSheet create_sprite_sheet(AssetHandle texture_handle);

    SpriteAnimation create_animation(SpriteSheet& sprite_sheet, uint32_t begin_frame, uint32_t end_frame, float frame_time);

private:
    AssetManager& m_asset_manager;
};

}