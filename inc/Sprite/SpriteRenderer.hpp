#pragma once 

#include "Asset/AssetManager.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Sprite/Sprite.hpp"

namespace AMB {

class SpriteRenderer {
public:
    SpriteRenderer(AssetManager& asset_manager, Shader& shader);

    void change_sprite(Sprite& sprite);

    void draw(const mat::Mat4f& mvp);

private:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;

    std::vector<SpriteVertex> m_vertex;
    std::vector<uint32_t> m_index;

    Shader& m_shader;

    VertexAttribLayout m_layout;
    AssetManager& m_asset_manager;
    Texture* m_texture;
};

}