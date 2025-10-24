#pragma once

#include "Asset/AssetManager.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Sprite/Sprite.hpp"

namespace AMB {

class SpriteBatchRenderer {
public:
    SpriteBatchRenderer(AssetManager& asset_manager, Shader& shader, AssetHandle texture_handle, uint32_t reserve = 1024);

    void submit_sprite(Sprite& sprite);

    void build_mesh();

    void reset();

    void draw(const mat::Mat4f& mvp);

private:
    AssetManager& m_asset_manager;
    Shader& m_shader;
    AssetHandle m_texture_handle;

    uint32_t m_sprite_count;

    std::vector<SpriteVertex> m_vertex;
    std::vector<uint32_t> m_index;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
    VertexAttribLayout m_layout;
};

}