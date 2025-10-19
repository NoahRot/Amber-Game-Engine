#pragma once

#include <glad/glad.h>

#include "Graphic/VertexArray.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/Shader.hpp"

namespace AMB {

class Renderer {
public:

    Renderer();

    void clear();

    void set_clear_color(float r, float g, float b, float a);

    void set_depth_test(bool enable);

    void set_blend(bool enable);

    void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);

    void draw_arrays(std::shared_ptr<VertexArray> vao, Shader& shader);

private:

};

}