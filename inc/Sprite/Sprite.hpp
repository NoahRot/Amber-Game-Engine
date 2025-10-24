#pragma once

#include <vector>

#include "Asset/AssetHandle.hpp"
#include "Asset/AssetManager.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

#include "mat/Math.hpp"

namespace AMB {

struct SpriteVertex {
    float x, y, z;
    float u, v;
};

class Sprite {
public:
    Sprite()
    : m_texture_handle({-1, typeid(Texture)}), m_position(), m_dimension(), m_texture_coord(), m_texture_dim()
    {}

    Sprite(AssetHandle texture, mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim)
    : m_texture_handle(texture), m_position(position), m_dimension(dimension), m_texture_coord(texture_coord), m_texture_dim(texture_dim)
    {}

    AssetHandle get_texture_handle() const { return m_texture_handle; }

    mat::Vec3f& get_position() { return m_position; }
    mat::Vec2f& get_dimension() { return m_dimension; }

    mat::Vec2f& get_texture_coord() { return m_texture_coord; }
    mat::Vec2f& get_texture_dim() { return m_texture_dim; }

private:
    AssetHandle m_texture_handle;

    mat::Vec3f m_position;
    mat::Vec2f m_dimension;

    mat::Vec2f m_texture_coord;
    mat::Vec2f m_texture_dim;
};

}