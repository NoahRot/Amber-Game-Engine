#include "Graphic/PostProcessor.hpp"

namespace AMB {

PostProcessor::PostProcessor(uint32_t width, uint32_t height) 
: m_scene_fbo(width, height), m_pingpong_fbo{FrameBuffer(width, height), FrameBuffer(width, height)}, m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_width(width), m_height(height)
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
    glViewport(0, 0, m_scene_fbo.get_width(), m_scene_fbo.get_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::end(Shader& final_shader, PostProcessMode process_mode) {
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);


    int ping_pong_id = 0;
    uint32_t scene_texture = m_scene_fbo.get_color_texture();
    uint32_t effect_texture = scene_texture;

    for (size_t i = 0; i < m_shader_effects.size(); ++i) {
        m_pingpong_fbo[ping_pong_id].bind();

        m_shader_effects[i]->use_shader();
        m_shader_effects[i]->set_1i("u_texture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, effect_texture);

        draw_full_screen_quad();

        effect_texture = m_pingpong_fbo[ping_pong_id].get_color_texture();
        ping_pong_id = 1 - ping_pong_id; // Swap 0 <-> 1
    }

    // --- final pass to screen ---
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_width, m_height);

    final_shader.use_shader();

    if (process_mode == PostProcessMode::single) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, effect_texture);
        final_shader.set_1i("u_texture", 0);
    }
    else if (process_mode == PostProcessMode::multiple) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, scene_texture);
        final_shader.set_1i("u_scene", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, effect_texture);
        final_shader.set_1i("u_effect", 1);
    }

    draw_full_screen_quad();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_BLEND);

    glViewport(0, 0, m_width, m_height);
}

void PostProcessor::add_shader_effect(Shader* effect) {
    m_shader_effects.push_back(effect);
}

void PostProcessor::draw_full_screen_quad() {
    m_vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

}