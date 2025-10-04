#include "Graphic/IndexBuffer.hpp"

namespace AMB {

IndexBuffer::IndexBuffer(const void* data, uint32_t count, bool static_draw)
: m_count(count), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(uint32_t count, bool static_draw)
: m_count(count), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_index);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::index() const { 
    return m_index; 
}

uint32_t IndexBuffer::count() const { 
    return m_count; 
}

uint32_t IndexBuffer::size() const { 
    return m_count * sizeof(uint32_t); 
}

}