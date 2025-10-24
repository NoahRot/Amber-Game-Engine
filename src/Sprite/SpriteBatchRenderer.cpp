#include "Sprite/SpriteBatchRenderer.hpp"

namespace AMB {

SpriteBatchRenderer::SpriteBatchRenderer(AssetManager& asset_manager, Shader& shader, AssetHandle texture_handle, uint32_t reserve)
: m_asset_manager(asset_manager), m_shader(shader), m_texture_handle(texture_handle), 
    m_sprite_count(0), m_vertex(reserve * 4), m_index(reserve * 6),
    m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
{
    m_layout.add_float(3); // Position
    m_layout.add_float(2); // UV coordinates

    // Create vbo and ibo
    m_vbo = create_vertex_buffer<SpriteVertex>(m_vertex, false);
    m_ibo = create_index_buffer(m_index, false);
    m_vao = create_vertex_array();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

void SpriteBatchRenderer::submit_sprite(Sprite& sprite) {
    AssetHandle handle = sprite.get_texture_handle();
    if (handle.index != m_texture_handle.index || handle.type != m_texture_handle.type) {
        Logger::instance().log(LogLevel::Error, "SpriteBatchRenderer can not sent sprites with different texture to the same batch.");
    }

    if ((m_sprite_count + 1)*4 > m_vertex.size()) {
        Logger::instance().log(LogLevel::Warning, "SpriteBatchRenderer resize vectors");
        m_vertex.resize((m_sprite_count + 1)*4);
        m_index.resize((m_sprite_count + 1)*6);
    }

    uint32_t vert_id = m_sprite_count * 4;
    uint32_t ind_id = m_sprite_count * 6;

    mat::Vec3f pos = sprite.get_position();
    mat::Vec2f dim = sprite.get_dimension();
    mat::Vec2f uv_pos = sprite.get_texture_coord();
    mat::Vec2f uv_dim = sprite.get_texture_dim();

    m_vertex[vert_id + 0] = SpriteVertex{pos[0],        pos[1],        pos[2],   uv_pos[0],           uv_pos[1]          }; // Bottom left
    m_vertex[vert_id + 1] = SpriteVertex{pos[0]+dim[0], pos[1],        pos[2],   uv_pos[0]+uv_dim[0], uv_pos[1]          }; // Bottom right
    m_vertex[vert_id + 2] = SpriteVertex{pos[0]+dim[0], pos[1]+dim[1], pos[2],   uv_pos[0]+uv_dim[0], uv_pos[1]+uv_dim[1]}; // Top right
    m_vertex[vert_id + 3] = SpriteVertex{pos[0],        pos[1]+dim[1], pos[2],   uv_pos[0],           uv_pos[1]+uv_dim[1]}; // Top left

    m_index[ind_id + 0] = vert_id + 0;
    m_index[ind_id + 1] = vert_id + 1;
    m_index[ind_id + 2] = vert_id + 2;
    m_index[ind_id + 3] = vert_id + 2;
    m_index[ind_id + 4] = vert_id + 3;
    m_index[ind_id + 5] = vert_id + 0;

    m_sprite_count++;
}

void SpriteBatchRenderer::build_mesh() {
    m_vbo->update(m_vertex.data(), m_vertex.size() * sizeof(SpriteVertex));
    m_ibo->update(m_index.data(), m_index.size());
}

void SpriteBatchRenderer::reset() {
    m_sprite_count = 0;
}

void SpriteBatchRenderer::draw(const mat::Mat4f& mvp) {
    m_vao->bind();
    m_asset_manager.textures.get(m_texture_handle).bind(0);
    m_shader.use_shader();
    m_shader.set_mat4f("u_mvp", mvp);
    m_ibo->bind();

    glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

}