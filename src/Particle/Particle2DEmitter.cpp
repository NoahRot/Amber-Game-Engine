#include "Particle/Particle2DEmitter.hpp"

namespace AMB {

Emitter2D::Emitter2D(int32_t time_between_emission, void (*spawn)(mat::Vec2f&, mat::Vec2f&, mat::Vec4f&, mat::Vec2f&, float&),
    void (*update)(Particle2DContext&, float),
    uint32_t preallocate) 
: m_time_since_last_emit(0), m_time_between_emission(time_between_emission), m_particle_count(0), m_active(true), 
    m_vertex(4), m_spawn(spawn), m_update(update)
{
    // Preallocate memory
    m_storage.position.resize(preallocate);
    m_storage.dimension.resize(preallocate);
    m_storage.color.resize(preallocate);
    m_storage.velocity.resize(preallocate);
    m_storage.life_time.resize(preallocate);
}

void Emitter2D::activate() {
    m_active = true;
}

void Emitter2D::deactivate() {
    m_active = false;
}

bool Emitter2D::is_active() const {
    return m_active;
}

void Emitter2D::update(float dt) {
    // Spawn new particles
    if (m_active && m_spawn) {
        spawn(dt);
    }

    // Check size
    if (m_vertex.size() < 4*m_particle_count) { m_vertex.resize(m_particle_count*4); }

    // Loop over all active particles
    for (uint32_t i = 0; i < m_particle_count; /* no ++ */) {

        float& life = m_storage.life_time[i];

        // Check if alive
        life -= dt;
        if (life <= 0.0f) {
            kill_particle(i); // Kill if life time ended
            continue; // reprocess swapped particle
        }

        // Get the context
        Particle2DContext context{
            m_storage.position[i],
            m_storage.dimension[i],
            m_storage.color[i],
            m_storage.velocity[i],
            m_storage.life_time[i]
        };

        // Update all data
        if (m_update) { 
            m_update(context, dt); 
        }

        // Update the vertex and index data
        m_vertex[4*i + 0] = Particle2DVertex{context.position[0],                        context.position[1],                        context.color[0], context.color[1], context.color[2], context.color[3]};
        m_vertex[4*i + 1] = Particle2DVertex{context.position[0] + context.dimension[0], context.position[1],                        context.color[0], context.color[1], context.color[2], context.color[3]};
        m_vertex[4*i + 2] = Particle2DVertex{context.position[0] + context.dimension[0], context.position[1] + context.dimension[1], context.color[0], context.color[1], context.color[2], context.color[3]};
        m_vertex[4*i + 3] = Particle2DVertex{context.position[0],                        context.position[1] + context.dimension[1], context.color[0], context.color[1], context.color[2], context.color[3]};

        ++i;
    }
}

void Emitter2D::spawn_particles(uint32_t nbr_particles) {
    if (m_spawn) {
        for (uint32_t i(0) ; i < nbr_particles ; ++i) {
            capacity_check();

            m_spawn(m_storage.position[m_particle_count],
                    m_storage.dimension[m_particle_count],
                    m_storage.color[m_particle_count],
                    m_storage.velocity[m_particle_count],
                    m_storage.life_time[m_particle_count]);

            ++m_particle_count;
        }
    }
}

uint32_t Emitter2D::get_particle_count() const {
    return m_particle_count;
}

const std::vector<Particle2DVertex>& Emitter2D::get_particles() const {
    return m_vertex;
}

void Emitter2D::spawn(float dt) {
    m_time_since_last_emit += dt;
    int nbr_emission = m_time_since_last_emit/m_time_between_emission;
    m_time_since_last_emit = m_time_since_last_emit%m_time_between_emission;

    for (int i(0) ; i < nbr_emission ; ++i) {
        capacity_check();

        m_spawn(m_storage.position[m_particle_count],
                m_storage.dimension[m_particle_count],
                m_storage.color[m_particle_count],
                m_storage.velocity[m_particle_count],
                m_storage.life_time[m_particle_count]);

        ++m_particle_count;
    }
}

void Emitter2D::kill_particle(uint32_t id) {
    --m_particle_count;
    std::swap(m_storage.position[id], m_storage.position[m_particle_count]);
    std::swap(m_storage.dimension[id], m_storage.dimension[m_particle_count]);
    std::swap(m_storage.color[id], m_storage.color[m_particle_count]);
    std::swap(m_storage.velocity[id], m_storage.velocity[m_particle_count]);
    std::swap(m_storage.life_time[id], m_storage.life_time[m_particle_count]);
}

void Emitter2D::capacity_check() {
    if (m_particle_count == m_storage.life_time.size()) {
        uint32_t new_size = m_storage.life_time.size()*2+1;
        m_storage.position.resize(new_size);
        m_storage.dimension.resize(new_size);
        m_storage.color.resize(new_size);
        m_storage.velocity.resize(new_size);
        m_storage.life_time.resize(new_size);
    }
}

}