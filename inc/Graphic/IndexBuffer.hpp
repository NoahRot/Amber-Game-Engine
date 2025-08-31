#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

namespace AMB {

class IndexBuffer {
public:
    IndexBuffer(const void* data, uint32_t count, bool static_draw = true)
    : m_count(count), m_static_draw(static_draw)
    {
        glGenBuffers(1, &m_index);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
        GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IndexBuffer(uint32_t count, bool static_draw = true)
    : m_count(count), m_static_draw(static_draw)
    {
        glGenBuffers(1, &m_index);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
        GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~IndexBuffer() {
        glDeleteBuffers(1, &m_index);
    }

    // No copy (OpenGL resources shouldn’t be copied blindly)
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    }

    void unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t index() const { return m_index; }

    uint32_t count() const { return m_count; }

    uint32_t size() const { return m_count * sizeof(uint32_t); }

private:
    uint32_t m_index;
    uint32_t m_count;
    bool m_static_draw;
};

}