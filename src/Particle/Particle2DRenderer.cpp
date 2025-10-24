#include "Particle/Particle2DRenderer.hpp"

namespace AMB {

Particle2DRenderer::Particle2DRenderer(Shader& shader)
: m_shader(shader)
{}

void Particle2DRenderer::draw(Particle2DSystem& system) {
    std::shared_ptr<VertexArray> vao = system.get_vertex_array();
    vao->bind();
    m_shader.use_shader();
    glDrawArrays(GL_POINTS, 0, system.size());
}

}