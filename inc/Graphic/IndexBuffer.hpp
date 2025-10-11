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

    void update(const uint32_t* data, uint32_t size);

    void change_capacity(uint32_t new_capacity, bool conserve_data);

private:
    uint32_t m_index;
    uint32_t m_count;
    uint32_t m_capacity;
    bool m_static_draw;
};

std::shared_ptr<IndexBuffer> create_index_buffer(const std::vector<uint32_t>& indices, bool static_draw = true);

std::shared_ptr<IndexBuffer> create_index_buffer(uint32_t capacity, bool static_draw = true);

}