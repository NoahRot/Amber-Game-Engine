#pragma once

#include "Particle/Particle2D.hpp"

namespace AMB {

class Particle2DSystem {
public:
    Particle2DSystem(uint32_t max_particles = 1024);

    void update(float dt);

    void update(float dt, void (*update_fnc)(Particle2D&, float));

    std::vector<Particle2D>& get_particles();

    void add_particle(const Particle2D& p);

    std::shared_ptr<VertexArray> get_vertex_array();

    uint32_t size() const;

private:
    std::vector<Particle2D> m_particles;
    uint32_t m_size;

    VertexAttribLayout m_layout;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<VertexArray> m_vao;
};

}