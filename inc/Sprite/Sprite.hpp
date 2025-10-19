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

class SpriteSheet {
public:
    SpriteSheet(AssetHandle texture_handle)
    : m_texture_handle(texture_handle)
    {}

    uint32_t add_sprite(mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim) {
        m_sprites.push_back(Sprite(m_texture_handle, position, dimension, texture_coord, texture_dim));
        return m_sprites.size() - 1;
    }

    Sprite get_sprite(uint32_t id) {
        return m_sprites.at(id);
    }

    bool validity(uint32_t id) const {
        return id < m_sprites.size();
    }

    uint32_t size() const {
        return m_sprites.size();
    }

private:
    AssetHandle m_texture_handle;
    std::vector<Sprite> m_sprites;
};

class SpriteAnimation {
public:
    SpriteAnimation(SpriteSheet& sprite_sheet, uint32_t begin_sprite, uint32_t end_sprite, uint32_t frame_time)
    : m_sprite_sheet(sprite_sheet), m_begin_sprite(begin_sprite), m_end_sprite(end_sprite), m_current_sprite(begin_sprite),
      m_frame_time(frame_time), m_current_time(0)
    {}

    void update(uint32_t dt) {
        m_current_time += dt;
        while(m_current_time > m_frame_time) {
            ++m_current_sprite;
            if (m_current_sprite > m_end_sprite) {
                m_current_sprite = m_begin_sprite;
            }
            m_current_time -= m_frame_time;
        }
    }

    Sprite get_current_sprite() {
        return m_sprite_sheet.get_sprite(m_current_sprite);
    }

private:
    SpriteSheet& m_sprite_sheet;
    uint32_t m_begin_sprite, m_end_sprite, m_current_sprite;
    uint32_t m_frame_time, m_current_time;
};

class SpriteFactory {
public:
    SpriteFactory(AssetManager& asset_manager)
    : m_asset_manager(asset_manager)
    {}

    Sprite create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension, mat::Vec2f uv_coord, mat::Vec2f uv_dim) {
        if (!m_asset_manager.textures.validity(texture_handle)) {
            Logger::instance().log(Error, "Sprite Factory can not create sprite. Texture handle is invalid.");
            return Sprite();
        }

        return Sprite(texture_handle, position, dimension, uv_coord, uv_dim);        
    }

    Sprite create_single_texture_sprite(AssetHandle texture_handle, mat::Vec3f position, mat::Vec2f dimension) {
        return create_single_texture_sprite(texture_handle, position, dimension, {0.0f, 0.0f}, {1.0f, 1.0f});        
    }

    SpriteSheet create_sprite_sheet_quad(AssetHandle texture_handle, mat::Vec2i quad_dim, mat::Vec2f sprite_dim) {
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

    SpriteSheet create_sprite_sheet(AssetHandle texture_handle) {
        SpriteSheet sprite_sheet(texture_handle);
        if (!m_asset_manager.textures.validity(texture_handle)) {
            Logger::instance().log(Error, "Sprite Factory can not create sprite. Texture handle is invalid.");
            return sprite_sheet;
        }
        return sprite_sheet;
    }

    SpriteAnimation create_animation(SpriteSheet& sprite_sheet, uint32_t begin_frame, uint32_t end_frame, float frame_time) {
        if (begin_frame > end_frame) {
            std::swap(begin_frame, end_frame);
        }

        if (!sprite_sheet.validity(end_frame)) {
            Logger::instance().log(Error, "Sprite Factory can not create sprite animation. Frame index out of range.");
        }

        return SpriteAnimation(sprite_sheet, begin_frame, end_frame, frame_time);
    }

private:
    AssetManager& m_asset_manager;
};

class SpriteRenderer {
public:
    SpriteRenderer(AssetManager& asset_manager, Shader& shader) 
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

    void change_sprite(Sprite& sprite) {
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

    void draw(const mat::Mat4f& mvp) {
        m_vao->bind();
        m_texture->bind(0);
        m_shader.use_shader();
        m_shader.set_mat4f("u_mvp", mvp);
        m_ibo->bind();

        glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

        m_vao->unbind();
    }

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

class SpriteBatchRenderer {
public:
    SpriteBatchRenderer(AssetManager& asset_manager, Shader& shader, AssetHandle texture_handle, uint32_t reserve = 1024)
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

    void submit_sprite(Sprite& sprite) {
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

    void build_mesh() {
        m_vbo->update(m_vertex.data(), m_vertex.size() * sizeof(SpriteVertex));
        m_ibo->update(m_index.data(), m_index.size());
    }

    void reset() {
        m_sprite_count = 0;
    }

    void draw(const mat::Mat4f& mvp) {
        Logger& logger = Logger::instance();

        m_vao->bind();
        m_asset_manager.textures.get(m_texture_handle).bind(0);
        m_shader.use_shader();
        m_shader.set_mat4f("u_mvp", mvp);
        m_ibo->bind();

        glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

        m_vao->unbind();
    }

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