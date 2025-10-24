#include "Sprite/SpriteFactory.hpp"

namespace AMB {

SpriteFactory::SpriteFactory(AssetManager& asset_manager)
: m_asset_manager(asset_manager)
{}

Sprite SpriteFactory::create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f uv_coord, mat::Vec2f uv_dim) {
    if (!m_asset_manager.textures.validity(texture_handle)) {
        Logger::instance().log(Error, "Sprite Factory can not create sprite. Texture handle is invalid.");
        return Sprite();
    }

    return Sprite(texture_handle, position, dimension, uv_coord, uv_dim);        
}

Sprite SpriteFactory::create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension) {
    return create_single_texture_sprite(texture_handle, position, dimension, {0.0f, 0.0f}, {1.0f, 1.0f});        
}

SpriteSheet SpriteFactory::create_sprite_sheet_quad(AssetHandle texture_handle, mat::Vec2i quad_dim, mat::Vec2f sprite_dim) {
    SpriteSheet sprite_sheet(texture_handle);
    if (!m_asset_manager.textures.validity(texture_handle)) {
        Logger::instance().log(Error, "Sprite Factory can not create sprite. Texture handle is invalid.");
        return sprite_sheet;
    }
    Texture& texture = m_asset_manager.textures.get(texture_handle);

    float width = (float)quad_dim[0]/(float)texture.get_width();
    float height = (float)quad_dim[1]/(float)texture.get_height();
    uint32_t col = texture.get_width()/quad_dim[0];
    uint32_t row = texture.get_height()/quad_dim[1];

    for (uint32_t j(0) ; j < row ; ++j) {
        for (uint32_t i(0) ; i < col ; ++i) {
            sprite_sheet.add_sprite({0.0f, 0.0f, 0.0f}, sprite_dim, {i*width, j*height}, {width, height});
        }
    }

    return sprite_sheet;
}

SpriteSheet SpriteFactory::create_sprite_sheet(AssetHandle texture_handle) {
    SpriteSheet sprite_sheet(texture_handle);
    if (!m_asset_manager.textures.validity(texture_handle)) {
        Logger::instance().log(Error, "Sprite Factory can not create sprite. Texture handle is invalid.");
        return sprite_sheet;
    }
    return sprite_sheet;
}

SpriteAnimation SpriteFactory::create_animation(SpriteSheet& sprite_sheet, uint32_t begin_frame, uint32_t end_frame, float frame_time) {
    if (begin_frame > end_frame) {
        std::swap(begin_frame, end_frame);
    }

    if (!sprite_sheet.validity(end_frame)) {
        Logger::instance().log(Error, "Sprite Factory can not create sprite animation. Frame index out of range.");
    }

    return SpriteAnimation(sprite_sheet, begin_frame, end_frame, frame_time);
}

}