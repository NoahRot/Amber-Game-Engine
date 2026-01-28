#pragma once

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"
#include "UI/Vertex.hpp"
#include "Logger/Logger.hpp"
#include "Text/Font.hpp"

namespace AMB::UI {

class UI_Renderer {
public:
    UI_Renderer(Shader& shader, AMB::Texture& texture, Font& font, uint32_t reserve = 0);

    void submit_quad(UI_Vertex vertices[4]);

    Font& get_font() const;

    void build_mesh();

    void reset();

    void draw(const mat::Mat4f& mvp);

private:
    std::vector<UI_Vertex> m_vertex;
    std::vector<uint32_t> m_index;
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
    VertexAttribLayout m_layout;
    Shader& m_shader;
    AMB::Texture& m_texture;
    Font& m_font;
    uint32_t m_quad_count;
};

}