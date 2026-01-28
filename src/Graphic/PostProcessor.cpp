#include "Graphic/PostProcessor.hpp"

namespace AMB {

PostProcessor::PostProcessor(uint32_t width, uint32_t height) 
: m_scene_fbo(width, height), m_pingpong_fbo{FrameBuffer(width, height), FrameBuffer(width, height)}, m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
{
    VertexAttribLayout layout;
    layout.add_float(2); // Position
    layout.add_float(2); // UV coordinates

    std::vector<PostProcessorVertex> vertex = {
        PostProcessorVertex{-1.0f, -1.0f, 0.0f, 0.0f},
        PostProcessorVertex{ 1.0f, -1.0f, 1.0f, 0.0f},
        PostProcessorVertex{ 1.0f,  1.0f, 1.0f, 1.0f},
        PostProcessorVertex{-1.0f,  1.0f, 0.0f, 1.0f}
    };

    std::vector<uint32_t> index = {
        0, 1, 2,
        2, 3, 0
    };

    // Create vbo and ibo
    m_vbo = create_vertex_buffer<PostProcessorVertex>(vertex, true);
    m_ibo = create_index_buffer(index, true);
    m_vao = create_vertex_array();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

void PostProcessor::begin() {
    m_scene_fbo.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::end(Shader& final_shader) {
    int ping_pong_id = 0;
    uint32_t input_texture = m_scene_fbo.get_color_texture();

    for (size_t i = 0; i < m_shader_effects.size(); ++i) {
        m_pingpong_fbo[ping_pong_id].bind();

        m_shader_effects[i]->use_shader();
        m_shader_effects[i]->set_1i("u_texture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, input_texture);

        draw_full_screen_quad();

        input_texture = m_pingpong_fbo[ping_pong_id].get_color_texture();
        ping_pong_id = 1 - ping_pong_id; // Swap 0 <-> 1
    }

    // final pass to screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    final_shader.use_shader();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, input_texture);
    final_shader.set_1i("u_texture", 0);          // make sure the shader sampler uses unit 0
    draw_full_screen_quad();
}

void PostProcessor::add_shader_effect(Shader* effect) {
    m_shader_effects.push_back(effect);
}

void PostProcessor::draw_full_screen_quad() {
    m_vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

}