#pragma once

#include <string>

#include "Text/Font.hpp"
#include "mat/Math.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

namespace AMB {

struct VertexText {
    float x, y, z;     // Position
    float u, v;        // Texture coordinates
};

class TextRenderer {
public:
    TextRenderer(Font& font, Shader& shader, const std::string& text, float r, float g, float b, const mat::Vec3f& position, uint32_t reserve = 100)
    : m_font(font), m_shader(shader), m_text(text), m_r(r), m_g(g), m_b(b), m_position(position), m_vertex(), m_index(),
      m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_text_layout()
    {
        // Create text layout
        m_text_layout.add_float(3); // Add the position
        m_text_layout.add_float(2); // Add the texture coordinates

        // Reserve space
        m_vertex.reserve(4 * reserve);
        m_index.reserve(6 * reserve);
    }

    ~TextRenderer() {}

    Font& get_font() {
        return m_font;
    }

    void set_text(const std::string& text) {
        m_text = text;
    }

    std::string get_text() const {
        return m_text;
    }

    uint32_t get_size() const {
        return m_text.size();
    }

    void set_color(float r, float g, float b) {
        m_r = r;
        m_g = g;
        m_b = b;
    }

    void get_color(float& r, float& g, float& b) const {
        r = m_r;
        g = m_g;
        b = m_b;
    }

    void set_position(const mat::Vec3f& position) {
        m_position = position;
    }

    mat::Vec3f get_position() const {
        return m_position;
    }

    void build_mesh(float r, float g, float b) {
        float current_x(0), current_y(0);

        for (uint32_t i(0) ; i < m_text.size() ; ++i) {
            if (m_text[i] == '\n') {
                current_x = 0;
                current_y -= m_font.get_height();

            }else{
                const Character& c = m_font.get_char(m_text[i]);

                float x_(m_position[0] + current_x + c.bearing_x);
                float y_(m_position[1] + current_y - c.height + c.bearing_y);

                uint32_t vert_index = m_vertex.size();

                m_vertex.push_back(VertexText{x_,           y_,             0,    c.u,        c.v + c.h }); // Bottom left
                m_vertex.push_back(VertexText{x_ + c.width, y_,             0,   c.u + c.w,  c.v + c.h }); // Bottom right
                m_vertex.push_back(VertexText{x_ + c.width, y_ + c.height,  0,   c.u + c.w,  c.v       }); // Top right
                m_vertex.push_back(VertexText{x_,           y_ + c.height,  0,   c.u,        c.v       }); // Top left

                m_index.push_back(vert_index + 0);
                m_index.push_back(vert_index + 1);
                m_index.push_back(vert_index + 2);

                m_index.push_back(vert_index + 2);
                m_index.push_back(vert_index + 3);
                m_index.push_back(vert_index + 0);

                current_x += c.advance >> 6;
            }
        }

        // Create vbo and ibo
        m_vbo = create_vertex_buffer<VertexText>(m_vertex, false);
        m_ibo = create_index_buffer(m_index, false);
        m_vao = create_vertex_array();

        m_vao->bind();
        m_vao->add_vertex_buffer(m_vbo, m_text_layout);
        m_vao->set_index_buffer(m_ibo);
        m_vao->unbind();
    }

    void reset() {
        m_vertex.clear();
        m_index.clear();
    }

    void draw() {
        m_vao->bind();
        m_shader.use_shader();
        m_shader.set_4f("u_color", {m_r, m_g, m_b, 1.0f});
        m_ibo->bind();

        glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

        m_vao->unbind();
    }

private:
    Font& m_font;
    Shader& m_shader;

    std::string m_text;
    float m_r, m_g, m_b;
    mat::Vec3f m_position;

    std::vector<VertexText> m_vertex;
    std::vector<uint32_t> m_index;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
    VertexAttribLayout m_text_layout;
};

}