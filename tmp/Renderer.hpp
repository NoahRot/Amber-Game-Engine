#pragma once

#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/VertexArray.hpp"
#include "Text/Font.hpp"

#include "UI/Type.hpp"

namespace AMB::UI {

class Renderer {
public:
    Renderer(Shader& shader, Texture& texture, Font& font, uint32_t reserve = 128);

    void submit_quad(Vertex vertices[4]);

    void build_mesh();

    void reset();

    void draw(const mat::Mat4f& mvp);

    Font& get_font();

private:
    std::vector<Vertex> m_vertex;
    std::vector<uint32_t> m_index;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;

    Shader& m_shader;
    Texture& m_texture;
    Font& m_font;

    uint32_t m_quad_count;
};

}