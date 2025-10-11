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
    float r, g, b, a;  // Color
    float u, v;        // Texture coordinates
};

class TextRenderer {
public:
    TextRenderer(Font& font, Shader& shader, float r, float g, float b, uint32_t reserve = 1024);

    ~TextRenderer();

    Font& get_font();

    void submit_text(const std::string& text, mat::Vec3f position, float r, float g, float b, float a = 1.0f);

    void build_mesh();

    void reset();

    void draw(const mat::Mat4f& mvp);

private:
    Font& m_font;
    Shader& m_shader;

    uint32_t m_char_count;

    std::vector<VertexText> m_vertex;
    std::vector<uint32_t> m_index;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
    VertexAttribLayout m_text_layout;
};

}