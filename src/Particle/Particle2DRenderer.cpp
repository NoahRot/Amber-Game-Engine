#include "Particle/Particle2DRenderer.hpp"

namespace AMB {

Particle2DRenderer::Particle2DRenderer(Shader& shader) 
: m_shader(shader)
{
    m_layout.add_float(2); // position
    m_layout.add_float(4); // color

    m_vbo = create_vertex_buffer<Particle2DVertex>(m_vertex, false);
    m_ibo = create_index_buffer(m_index, false);
    m_vao = create_vertex_array();
    m_vao->add_vertex_buffer(m_vbo, m_layout, sizeof(Particle2DVertex));
    m_vao->set_index_buffer(m_ibo);
}

void Particle2DRenderer::add_emitter(Emitter2D* emitter) {
    m_emitters.push_back(emitter);
}

void Particle2DRenderer::update() {
    // Calculate total particle count
    m_size = 0;
    for (auto& emitter : m_emitters) {
        m_size += emitter->get_particle_count();
    }

    if (m_vertex.size() < m_size*4) {
        m_vertex.resize(m_size*4);
    }
    if (m_index.size() < m_size*6) {
        resize_index();
    }

    // Copy particles from emitters
    uint32_t offset = 0;
    for (auto& emitter : m_emitters) {
        const std::vector<AMB::Particle2DVertex>& particles = emitter->get_particles(); // you need to expose this
        uint32_t count = emitter->get_particle_count();

        std::copy(particles.begin(), particles.begin() + count*4, m_vertex.begin() + offset*4);
        offset += count;
    }

    // Update VBO & IBO
    m_vbo->update(m_vertex.data(), m_size * 4 * sizeof(Particle2DVertex));
    m_ibo->update(m_index.data(), m_size * 6);
}

void Particle2DRenderer::draw(const mat::Mat4f& mvp) {
    // Draw particles to scene FBO
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_vao->bind();
    m_shader.use_shader();
    m_shader.set_mat4f("u_mvp", mvp);
    m_ibo->bind();

    glDrawElements(GL_TRIANGLES, m_ibo->count(), GL_UNSIGNED_INT, 0);

    // Restore states if needed
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    m_vao->unbind();
}

void Particle2DRenderer::resize_index() {
    uint32_t old_nbr_part = m_index.size()/6;
    uint32_t new_nbr_part = m_size;

    m_index.resize(new_nbr_part*6);
    for (uint32_t i(old_nbr_part) ; i < new_nbr_part ; ++i) {
        m_index[i*6 + 0] = i*4 + 0;
        m_index[i*6 + 1] = i*4 + 1;
        m_index[i*6 + 2] = i*4 + 2;
        
        m_index[i*6 + 3] = i*4 + 2;
        m_index[i*6 + 4] = i*4 + 3;
        m_index[i*6 + 5] = i*4 + 0;
    }
}

}