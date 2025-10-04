#include "Graphic/VertexBuffer.hpp"

namespace AMB {

VertexBuffer::VertexBuffer(const void* data, uint32_t size, bool static_draw) 
: m_size(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    bind();
    GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}

VertexBuffer::VertexBuffer(uint32_t size, bool static_draw)
: m_size(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    bind();
    GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    std::vector<char> empty_data(size, 0);
    glBufferData(GL_ARRAY_BUFFER, size, &empty_data, usage);
    unbind();
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_index);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t VertexBuffer::index() const { 
    return m_index; 
}

uint32_t VertexBuffer::size() const { 
    return m_size; 
}

}