#pragma once

#include <vector>
#include <array>
#include <stack>
#include <random>
#include <functional>

#include "mat/Math.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Shader.hpp"
#include "Random/Lehmer.hpp"

namespace AMB {

struct Particle2DStorage {
	std::vector<mat::Vec2f> position;
	std::vector<mat::Vec2f> dimension;
	std::vector<mat::Vec4f> color;
	std::vector<mat::Vec2f> velocity;
	std::vector<float> 	life_time;
};

struct Particle2DContext {
	mat::Vec2f& position;
	mat::Vec2f& dimension;
	mat::Vec4f& color;
	mat::Vec2f& velocity;
	float& life_time;
};

struct Particle2DVertex {
	float x, y;
	float r, g, b, a;
};

}