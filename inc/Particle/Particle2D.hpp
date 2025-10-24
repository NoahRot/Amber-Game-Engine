#pragma once

#include <vector>
#include <stack>
#include <random>

#include "mat/Math.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Shader.hpp"
#include "Random/Lehmer.hpp"

namespace AMB {

struct Particle2D {
    Particle2D()
    : position({0.0f, 0.0f}), r(1.0f), g(1.0f), b(1.0f), a(1.0f), size(1.0f), 
      velocity({0.0f, 0.0f}), life_time(1000)
    {}

    mat::Vec2f position;
    float r, g, b, a;
    float size;

    mat::Vec2f velocity;
    int32_t life_time;
};

}