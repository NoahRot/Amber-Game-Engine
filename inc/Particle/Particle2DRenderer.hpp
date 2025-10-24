#pragma once

#include "Graphic/Shader.hpp"
#include "Particle/Particle2DSystem.hpp"

namespace AMB {

class Particle2DRenderer {
public:
    Particle2DRenderer(Shader& shader);

    void draw(Particle2DSystem& system);

private:
    Shader& m_shader;
};

}