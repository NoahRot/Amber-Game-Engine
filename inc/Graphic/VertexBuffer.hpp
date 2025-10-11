#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

namespace AMB {

class VertexBuffer {
public:
    VertexBuffer(const void* data, uint32_t size, bool static_draw = true);

    VertexBuffer(uint32_t size, bool static_draw = true);

    ~VertexBuffer();

    // No copy (OpenGL resources shouldn’t be copied blindly)
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void bind() const;

    void unbind() const;

    uint32_t index() const;

    uint32_t size() const;

    void update(const void* data, uint32_t size, uint32_t offset = 0) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        unbind();
    }

    void change_data(const void* data, uint32_t size) {
        bind();
        GLenum usage = m_static_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        unbind();
    }

private:
    uint32_t m_index;
    uint32_t m_size;
    bool m_static_draw;
};

template<typename T>
std::shared_ptr<VertexBuffer> create_vertex_buffer(const std::vector<T>& data, bool static_draw = true) {
    return std::make_shared<VertexBuffer>(data.data(), data.size() * sizeof(T), static_draw);
}

std::shared_ptr<VertexBuffer> create_vertex_buffer(uint32_t size, bool static_draw = true);

}