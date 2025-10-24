#include "Particle/Particle2DSystem.hpp"

namespace AMB {

Particle2DSystem::Particle2DSystem(uint32_t max_particles)
: m_particles(max_particles), m_size(0)
{
    m_layout.add_float(2); // position
    m_layout.add_float(4); // color
    m_layout.add_float(1); // size

    m_vbo = create_vertex_buffer(m_particles, false);
    m_vao = create_vertex_array();
    m_vao->add_vertex_buffer(m_vbo, m_layout, sizeof(Particle2D));
}

void Particle2DSystem::update(float dt) {
    for (uint32_t i(0) ; i < m_size ; ++i) {
        Particle2D& p = m_particles[i];
        p.position += p.velocity * dt;
        p.life_time -= static_cast<uint32_t>(dt);

        if (p.life_time <= 0) {
            std::swap(m_particles[i], m_particles[m_size - 1]);
            --m_size;
        }

    }

    m_vbo->update(m_particles.data(), m_particles.size()*sizeof(Particle2D), 0);
}

void Particle2DSystem::update(float dt, void (*update_fnc)(Particle2D&, float)) {
    for (uint32_t i(0) ; i < m_size ; ++i) {
        Particle2D& p = m_particles[i];
        
        update_fnc(p, dt);
        
        p.life_time -= static_cast<uint32_t>(dt);
        if (p.life_time <= 0) {
            std::swap(m_particles[i], m_particles[m_size - 1]);
            --m_size;
        }

    }

    m_vbo->update(m_particles.data(), m_particles.size()*sizeof(Particle2D), 0);
}

std::vector<Particle2D>& Particle2DSystem::get_particles() {
    return m_particles;
}

void Particle2DSystem::add_particle(const Particle2D& p) {
    if (m_size < m_particles.size()) {
        m_particles[m_size] = p;
        ++m_size;
    }
}

std::shared_ptr<VertexArray> Particle2DSystem::get_vertex_array() {
    return m_vao;
}

uint32_t Particle2DSystem::size() const {
    return m_size;
}

}