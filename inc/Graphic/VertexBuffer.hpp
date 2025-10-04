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

private:
    uint32_t m_index;
    uint32_t m_size;
    bool m_static_draw;
};

}