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
    VertexArray() {
        glGenVertexArrays(1, &m_index);
        glBindVertexArray(m_index);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &m_index);
    }

    void bind() const {
        glBindVertexArray(m_index);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb, const VertexAttribLayout& layout) {

        // Bind VAO and VBO
        bind();
        vb->bind();

        // Prepare the offset for attribute pointers
        uint32_t offset = 0;

        // Iterate over the layout and configure each attribute
        for (uint32_t i = 0; i < layout.size(); ++i) {
            const auto& attrib = layout.get(i);

            // Enable the attribute at index i
            glEnableVertexAttribArray(i);

            // Configure the attribute pointer
            glVertexAttribPointer(
                i,                                          // Index of the attribute    
                attrib.size,                                // Number of components  
                attrib.type,                                // Type of data 
                attrib.normalized ? GL_TRUE : GL_FALSE,     // Normalize flag
                layout.stride(),                            // Stride (space between consecutive attributes)
                (const void*)offset                         // Offset within the buffer (from the start of the buffer)
            );

            // Update the offset
            offset += attrib.stride;  // Increment the offset by the attribute's stride
        }

        // Add the vertex buffer to the list of vertex buffers for this VAO
        m_vertex_buffers.push_back(vb);

        // Unbind VBO and VAO to prevent accidental modification
        vb->unbind();
        unbind();
    }

    void set_index_buffer(const std::shared_ptr<IndexBuffer>& ib) {
        m_index_buffer = ib;
    }

    uint32_t index() const { return m_index; }

private:
    uint32_t m_index = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;
};

}