#include "Graphic/VertexArray.hpp"

namespace AMB {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_index);
    glBindVertexArray(m_index);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_index);
}

void VertexArray::bind() const {
    glBindVertexArray(m_index);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb, const VertexAttribLayout& layout) {

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
            reinterpret_cast<void*>(offset)             // Offset within the buffer (from the start of the buffer)
        );

        // Update the offset
        offset += attrib.stride;  // Increment the offset by the attribute's stride
    }

    // Add the vertex buffer to the list of vertex buffers for this VAO
    m_vertex_buffers.push_back(vb);
}

void VertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb, const VertexAttribLayout& layout, uint32_t overwrite_stride) {
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
            overwrite_stride,                           // Stride (space between consecutive attributes)
            reinterpret_cast<void*>(offset)             // Offset within the buffer (from the start of the buffer)
        );

        // Update the offset
        offset += attrib.stride;  // Increment the offset by the attribute's stride
    }

    // Add the vertex buffer to the list of vertex buffers for this VAO
    m_vertex_buffers.push_back(vb);

    // Unbind VBO and VAO to prevent accidental modification
}

void VertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& ib) {
    bind();                    // Critical: VAO must be bound
    if (ib) {
        ib->bind();            // Bind the index buffer
    } else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // Optional: unbind if nullptr
    }
    m_index_buffer = ib;
}

std::shared_ptr<IndexBuffer> VertexArray::get_index_buffer() {
    return m_index_buffer;
}

uint32_t VertexArray::index() const { 
    return m_index; 
}

std::shared_ptr<VertexArray> create_vertex_array(){
    return std::make_shared<VertexArray>();
}

}