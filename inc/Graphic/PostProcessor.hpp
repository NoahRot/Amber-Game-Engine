#pragma once

#include <inttypes.h>
#include <memory>

#include "Graphic/FrameBuffer.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

namespace AMB {

struct PostProcessorVertex {
    float x, y;
    float u, v;
};

class PostProcessor {
public:
    PostProcessor(uint32_t width, uint32_t height);

    void begin(); // bind scene framebuffer

    void end(Shader& final_shader);   // apply effects and output to screen

    void add_shader_effect(Shader* effect);

private:
    void draw_full_screen_quad();

    FrameBuffer m_scene_fbo;
    FrameBuffer m_pingpong_fbo[2];

    std::vector<Shader*> m_shader_effects;
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;
};

}