#include "Text/Text.hpp"

namespace AMB {

TextRenderer::TextRenderer(Font& font, Shader& shader, float r, float g, float b, uint32_t reserve)
: m_font(font), m_shader(shader), m_char_count(0), m_vertex(), m_index(),
    m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_text_layout()
{
    // Create text layout
    m_text_layout.add_float(3); // Add the position
    m_text_layout.add_float(4); // Add the color
    m_text_layout.add_float(2); // Add the texture coordinates

    // Reserve space
    m_vertex.resize(4 * reserve);
    m_index.resize(6 * reserve);

    // Create vbo and ibo
    m_vbo = create_vertex_buffer<VertexText>(m_vertex, false);
    m_ibo = create_index_buffer(m_index, false);
    m_vao = create_vertex_array();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_text_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

TextRenderer::~TextRenderer() {}

Font& TextRenderer::get_font() {
    return m_font;
}

void TextRenderer::submit_text(const std::string& text, mat::Vec3f position, float r, float g, float b, float a) {
    float current_x(0), current_y(0);

    if ((m_char_count + text.size())*4 > m_vertex.size()) {
        Logger::instance().log(LogLevel::Warning, "TextRenderer resize vectors");
        m_vertex.resize((m_char_count + text.size())*4);
        m_index.resize((m_char_count + text.size())*6);
    }

    for (uint32_t i(0) ; i < text.size() ; ++i) {
        if (text[i] == '\n') {
            current_x = 0;
            current_y -= m_font.get_height();

        }else{
            const Character& c = m_font.get_char(text[i]);

            uint32_t vert_id = m_char_count * 4;
            uint32_t ind_id = m_char_count * 6;

            float x_(position[0] + current_x + c.bearing_x);
            float y_(position[1] + current_y - c.height + c.bearing_y);
            float z_(position[2]);

            m_vertex[vert_id + 0] = VertexText{x_,           y_,             z_, r, g, b, a,   c.u,        c.v + c.h }; // Bottom left
            m_vertex[vert_id + 1] = VertexText{x_ + c.width, y_,             z_, r, g, b, a,   c.u + c.w,  c.v + c.h }; // Bottom right
            m_vertex[vert_id + 2] = VertexText{x_ + c.width, y_ + c.height,  z_, r, g, b, a,   c.u + c.w,  c.v       }; // Top right
            m_vertex[vert_id + 3] = VertexText{x_,           y_ + c.height,  z_, r, g, b, a,   c.u,        c.v       }; // Top left

            m_index[ind_id + 0] = vert_id + 0;
            m_index[ind_id + 1] = vert_id + 1;
            m_index[ind_id + 2] = vert_id + 2;
            m_index[ind_id + 3] = vert_id + 2;
            m_index[ind_id + 4] = vert_id + 3;
            m_index[ind_id + 5] = vert_id + 0;

            current_x += c.advance >> 6;

            m_char_count += 1;
        }
    }
}

void TextRenderer::build_mesh() {
    m_vbo->update(m_vertex.data(), m_vertex.size() * sizeof(VertexText));
    m_ibo->update(m_index.data(), m_index.size());
}

void TextRenderer::reset() {
    m_char_count = 0;
}

void TextRenderer::draw(const mat::Mat4f& mvp) {
    m_vao->bind();
    m_font.get_texture().bind(0);
    m_shader.use_shader();
    m_shader.set_mat4f("u_mvp", mvp);
    m_ibo->bind();

    glDrawElements(GL_TRIANGLES, m_char_count*6, GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

}