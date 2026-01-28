#include "UI/Renderer.hpp"

namespace AMB::UI {

Renderer::Renderer(Shader& shader, Texture& texture, Font& font, uint32_t reserve)
: m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_shader(shader), m_texture(texture), m_font(font), m_quad_count(0)
{
    VertexAttribLayout layout;
    layout.add_float(2);    // position
    layout.add_float(4);    // color
    layout.add_float(2);    // uv
    layout.add_float(1);    // render_mode

    m_vertex.reserve(4 * reserve);
    m_index.reserve(6 * reserve);

    std::vector<Vertex> dummy_vertices(4 * reserve, Vertex{});
    std::vector<uint32_t> dummy_indices(6 * reserve, 0u);

    m_vbo = AMB::create_vertex_buffer<AMB::UI::Vertex>(dummy_vertices, false);
    m_ibo = AMB::create_index_buffer(dummy_indices, false);

    m_vao = create_vertex_array();

    m_vao->bind();
    m_vbo->bind();                       // optional but safe
    m_vao->add_vertex_buffer(m_vbo, layout);
    m_vao->set_index_buffer(m_ibo);       // now correctly captures IBO
    m_vao->unbind();

    Logger::instance().log(Debug, "UI renderer creation");
}

void Renderer::submit_quad(Vertex vertices[4]) {
    if ((m_quad_count + 1)*4 > m_vertex.size()) {
        Logger::instance().log(LogLevel::Warning, "UI Renderer resize vectors");
        m_vertex.resize((m_quad_count + 1)*4);
        m_index.resize((m_quad_count + 1)*6);
    }

    uint32_t vert_id = m_quad_count*4;
    uint32_t inde_id = m_quad_count*6;

    m_vertex[vert_id + 0] = vertices[0];
    m_vertex[vert_id + 1] = vertices[1];
    m_vertex[vert_id + 2] = vertices[2];
    m_vertex[vert_id + 3] = vertices[3];

    m_index[inde_id + 0] = vert_id + 0;
    m_index[inde_id + 1] = vert_id + 1;
    m_index[inde_id + 2] = vert_id + 2;
    m_index[inde_id + 3] = vert_id + 2;
    m_index[inde_id + 4] = vert_id + 3;
    m_index[inde_id + 5] = vert_id + 0;

    ++m_quad_count;
}

void Renderer::build_mesh() {
    m_vbo->update(m_vertex.data(), m_quad_count * 4 * sizeof(Vertex));
    m_ibo->update(m_index.data(), m_quad_count * 6);
}

void Renderer::reset()  {
    m_quad_count = 0;
}

void Renderer::draw(const mat::Mat4f& mvp) {
    m_shader.use_shader();
    m_texture.bind(0);
    m_font.get_texture().bind(1);
    m_shader.set_1i("u_texture", 0);  // ← Critical!
    m_shader.set_1i("u_font", 1);     // ← Critical!
    m_vao->bind();
    m_shader.set_mat4f("u_mvp", mvp);

    glDrawElements(GL_TRIANGLES, m_quad_count*6, GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

Font& Renderer::get_font() {
    return m_font;
}

}