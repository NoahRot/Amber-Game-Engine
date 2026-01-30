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

    int get_width() { return m_width; }
    int get_height() {return m_height; }

private:
    uint32_t m_fbo;
    uint32_t m_color_texture;
    uint32_t m_rbo; // depth/stencil
    int m_width, m_height;
};

}