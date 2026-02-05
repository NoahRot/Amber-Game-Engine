#include "Graphic/PostProcessor.hpp"

namespace AMB {

PostProcessor::PostProcessor(uint32_t width, uint32_t height, AssetManager& asset_manager, AssetFactory& asset_factory) 
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

    // Load final/default shader
    std::string frag = 
    "#version 330 core\n"
    "in vec2 v_uv;\n"
    "out vec4 frag;\n"
    "uniform sampler2D u_texture;\n"

    "void main() {\n"
    "    frag = texture(u_texture, v_uv);\n"
    "}\n";

    std::string vert = 
    "#version 330 core\n"
    "layout(location = 0) in vec2 a_position;\n"
    "layout(location = 1) in vec2 a_uv;\n"
    "out vec2 v_uv;\n"
    "void main() {\n"
    "    v_uv = a_uv;\n"
    "    gl_Position = vec4(a_position, 0.0, 1.0);\n"
    "}\n";

    AMB::AssetHandle handle_shader = asset_factory.create_shader_from_code(vert, frag);
    if (!asset_manager.shaders.validity(handle_shader)) {
        Logger::instance().log(Fatal, "Postprocessor can not load final shader.");
        exit(EXIT_FAILURE);
    }
    m_final_shader = &asset_manager.shaders.get(handle_shader);
}

void PostProcessor::begin() {
    m_scene_fbo.bind();
    glViewport(0, 0, m_scene_fbo.get_width(), m_scene_fbo.get_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::add_effect(Shader* shader, PostProcessMode mode, bool scene_modifier) {
    m_effects.push_back(PostProcessEffects{shader, mode, scene_modifier});
}

void PostProcessor::clear_effect() {
    m_effects.clear();
}

void PostProcessor::end() {
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);


    int ping_pong_id = 0;
    uint32_t scene_texture = m_scene_fbo.get_color_texture();
    uint32_t effect_texture = scene_texture;

    for (auto& effect : m_effects) {
        m_pingpong_fbo[ping_pong_id].bind();
        effect.shader->use_shader();

        if(effect.mode == AMB::PostProcessMode::single) {

            if (effect.scene_modifier) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, scene_texture);
                effect.shader->set_1i("u_texture", 0);

            }else{
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, effect_texture);
                effect.shader->set_1i("u_texture", 0);
            }

        }else{

            if (effect.scene_modifier) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, scene_texture);
                effect.shader->set_1i("u_scene", 0);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, effect_texture);
                effect.shader->set_1i("u_effect", 1);
                
            }else{
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, scene_texture);
                effect.shader->set_1i("u_scene", 0);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, effect_texture);
                effect.shader->set_1i("u_effect", 1);
            }
        }

        draw_full_screen_quad();

        uint32_t output = m_pingpong_fbo[ping_pong_id].get_color_texture();

        if (effect.scene_modifier) {
            scene_texture = output;
            effect_texture = output;
        } else {
            effect_texture = output;
        }

        ping_pong_id = 1 - ping_pong_id; // Swap 0 <-> 1
    }

    // --- final pass ---
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_width, m_height);

    m_final_shader->use_shader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene_texture);
    m_final_shader->set_1i("u_texture", 0);

    draw_full_screen_quad();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_BLEND);

    glViewport(0, 0, m_width, m_height);
}

void PostProcessor::draw_full_screen_quad() {
    m_vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

}