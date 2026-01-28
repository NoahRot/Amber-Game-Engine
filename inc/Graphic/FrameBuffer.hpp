#pragma once

#include <inttypes.h>
#include <glad/glad.h>

#include "Logger/Logger.hpp"

namespace AMB{

class FrameBuffer {
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    void reset();

    void bind();
    void unbind();

    uint32_t get_color_texture() const;

private:
    uint32_t m_fbo;
    uint32_t m_color_texture;
    uint32_t m_rbo; // depth/stencil
    int m_width, m_height;
};

}