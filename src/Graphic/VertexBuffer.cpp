#include "Graphic/VertexBuffer.hpp"

namespace AMB {

VertexBuffer::VertexBuffer(const void* data, uint32_t size, bool static_draw) 
: m_size(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    bind();
    GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::VertexBuffer(uint32_t size, bool static_draw)
: m_size(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    bind();
    GLenum usage = static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    std::vector<char> empty_data(size, 0);
    glBufferData(GL_ARRAY_BUFFER, size, empty_data.data(), usage);
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

void VertexBuffer::update(const void* data, uint32_t size, uint32_t offset) {
    // Resize buffer if necessary
    if (m_size < size) {
        if (2*m_size < size) {
            change_capacity(size, false);
        }else{
            change_capacity(2*m_size, false);
        }
    }

    // Update data
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::change_capacity(uint32_t new_capacity, bool conserve_data) {
    glBindBuffer(GL_ARRAY_BUFFER, m_index);

    std::vector<unsigned char> old_data;
    uint32_t copy_size = std::min(new_capacity, m_size);

    if (conserve_data && m_size > 0) {
        old_data.resize(copy_size);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, copy_size, old_data.data());
    }

    glBufferData(GL_ARRAY_BUFFER, new_capacity, nullptr, m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    if (conserve_data && !old_data.empty()) {
        glBufferSubData(GL_ARRAY_BUFFER, 0, copy_size, old_data.data());
    }

    m_size = new_capacity;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<VertexBuffer> create_vertex_buffer(uint32_t size, bool static_draw) {
    return std::make_shared<VertexBuffer>(size, static_draw);
}

}