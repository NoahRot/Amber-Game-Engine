#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

namespace AMB {

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb, const VertexAttribLayout& layout);

    void set_index_buffer(const std::shared_ptr<IndexBuffer>& ib);

    uint32_t index() const;

private:
    uint32_t m_index = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;
};

}