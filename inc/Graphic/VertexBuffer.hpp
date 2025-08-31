#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

namespace AMB {

class VertexBuffer {
public:
    VertexBuffer(const void* data, uint32_t size, bool static_draw = true) 
    : m_size(size), m_static_draw(static_draw)
    {
        glGenBuffers(1, &m_index);
        bind();
        GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        unbind();
    }

    VertexBuffer(uint32_t size, bool static_draw = true)
    : m_size(size), m_static_draw(static_draw)
    {
        glGenBuffers(1, &m_index);
        bind();
        GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        std::vector<char> empty_data(size, 0);
        glBufferData(GL_ARRAY_BUFFER, size, &empty_data, usage);
        unbind();
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &m_index);
    }

    // No copy (OpenGL resources shouldn’t be copied blindly)
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_index);
    }

    void unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    uint32_t index() const { return m_index; }

    uint32_t size() const { return m_size; }

private:
    uint32_t m_index;
    uint32_t m_size;
    bool m_static_draw;
};

}