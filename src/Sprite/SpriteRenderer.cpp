#include "Sprite/SpriteRenderer.hpp"

namespace AMB {

SpriteRenderer::SpriteRenderer(AssetManager& asset_manager, Shader& shader) 
: m_vao(create_vertex_array()), m_vbo(create_vertex_buffer(4, false)), m_ibo(create_index_buffer(6, false)), 
    m_vertex(4, SpriteVertex{0.0f, 0.0f, 0.0f, 0.0f, 0.0f}), m_index(6),
    m_shader(shader), m_asset_manager(asset_manager), m_texture(nullptr)
{
    m_layout.add_float(3); // Position
    m_layout.add_float(2); // UV coordinates

    m_index[0] = 0;
    m_index[1] = 1;
    m_index[2] = 2;

    m_index[3] = 2;
    m_index[4] = 3;
    m_index[5] = 0;

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

void SpriteRenderer::change_sprite(Sprite& sprite) {
    if (!m_asset_manager.textures.validity(sprite.get_texture_handle())){
        Logger::instance().log(Error, "Sprite renderer can not change sprite. The texture handle is invalid.");
        return;
    }

    m_texture = &(m_asset_manager.textures.get(sprite.get_texture_handle()));

    mat::Vec3f pos = sprite.get_position();
    mat::Vec2f dim = sprite.get_dimension();
    mat::Vec2f uv_pos = sprite.get_texture_coord();
    mat::Vec2f uv_dim = sprite.get_texture_dim();

    m_vertex[0] = SpriteVertex{pos[0],        pos[1],        pos[2],   uv_pos[0],           uv_pos[1]          };
    m_vertex[1] = SpriteVertex{pos[0]+dim[0], pos[1],        pos[2],   uv_pos[0]+uv_dim[0], uv_pos[1]          };
    m_vertex[2] = SpriteVertex{pos[0]+dim[0], pos[1]+dim[1], pos[2],   uv_pos[0]+uv_dim[0], uv_pos[1]+uv_dim[1]};
    m_vertex[3] = SpriteVertex{pos[0],        pos[1]+dim[1], pos[2],   uv_pos[0],           uv_pos[1]+uv_dim[1]};

    m_vbo->update(m_vertex.data(), m_vertex.size()*sizeof(SpriteVertex));
    m_ibo->update(m_index.data(), m_index.size());
}

void SpriteRenderer::draw(const mat::Mat4f& mvp) {
    m_vao->bind();
    m_texture->bind(0);
    m_shader.use_shader();
    m_shader.set_mat4f("u_mvp", mvp);
    m_ibo->bind();

    glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

}