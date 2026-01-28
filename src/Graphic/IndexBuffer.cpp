#include "Graphic/IndexBuffer.hpp"

namespace AMB {

IndexBuffer::IndexBuffer(const void* data, uint32_t count, bool static_draw)
: m_count(count), m_capacity(count), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(uint32_t capacity, bool static_draw)
: m_count(0), m_capacity(capacity), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity * sizeof(uint32_t), nullptr, usage);
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

void IndexBuffer::update(const uint32_t* data, uint32_t count) {
    // Resize buffer if necessary
    if (m_capacity < count) {
        if (2*m_capacity < count) {
            change_capacity(count, false);
        }else{
            change_capacity(2*m_capacity, false);
        }
    }

    // Update data
    m_count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count*sizeof(uint32_t), data);
}

void IndexBuffer::change_capacity(uint32_t new_capacity, bool conserve_data) {
    bind();

    std::vector<uint32_t> old_data;
    uint32_t copy_count = std::min(new_capacity, m_count);

    if (conserve_data && m_count > 0) {
        old_data.resize(copy_count);
        glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, copy_count * sizeof(uint32_t), old_data.data());
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_capacity * sizeof(uint32_t), nullptr, m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    if (conserve_data && !old_data.empty()) {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, copy_count * sizeof(uint32_t), old_data.data());
    }

    m_capacity = new_capacity;
    m_count = copy_count;
    unbind();
}

std::shared_ptr<IndexBuffer> create_index_buffer(const std::vector<uint32_t>& indices, bool static_draw) {
    return std::make_shared<IndexBuffer>(indices.data(), indices.size(), static_draw);
}

std::shared_ptr<IndexBuffer> create_index_buffer(uint32_t capacity, bool static_draw) {
    return std::make_shared<IndexBuffer>(capacity, static_draw);
}

}