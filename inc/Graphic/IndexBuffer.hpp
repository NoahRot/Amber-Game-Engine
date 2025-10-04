#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

namespace AMB {

class IndexBuffer {
public:
    IndexBuffer(const void* data, uint32_t count, bool static_draw = true);

    IndexBuffer(uint32_t count, bool static_draw = true);

    ~IndexBuffer();

    // No copy (OpenGL resources shouldn’t be copied blindly)
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    void bind() const;

    void unbind() const;

    uint32_t index() const;

    uint32_t count() const;

    uint32_t size() const;

private:
    uint32_t m_index;
    uint32_t m_count;
    bool m_static_draw;
};

}