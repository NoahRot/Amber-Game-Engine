#include "Graphic/Layout.hpp"

namespace AMB {

uint32_t get_gl_enum_stride(uint32_t type) {
    switch(type) {
        case GL_FLOAT:
            return sizeof(float);
        case GL_UNSIGNED_INT:
            return sizeof(unsigned int);
        case GL_INT:
            return sizeof(int);
        case GL_BYTE:
            return sizeof(char);
        case GL_UNSIGNED_BYTE:
            return sizeof(unsigned char);
        case GL_SHORT:
            return sizeof(short int);
        case GL_UNSIGNED_SHORT:
            return sizeof(unsigned short int);
        default:
            return 0;
    }
}

VertexAttribLayout::VertexAttribLayout()
: m_stride(0)
{}

bool VertexAttribLayout::add_attrib(int32_t size, GLenum type, bool normalized) {
    // Get strid of the type
    uint32_t current_stride = get_gl_enum_stride(type);

    // Check if the type is valid
    if (current_stride == 0) {
        return false;
    }

    // Check if the size is valide
    if (size >= 1 && size <= 4) {
        // Push the new attribute
        m_attrib.push_back(VertexAttributes{size, type, normalized, current_stride*size});
        m_stride += current_stride*size;
        return true;
    }else{
        return false;
    }
}

bool VertexAttribLayout::add_float(int32_t size, bool normalized) {
    return add_attrib(size, GL_FLOAT, normalized);
}

bool VertexAttribLayout::add_unsigned_int(int32_t size, bool normalized) {
    return add_attrib(size, GL_UNSIGNED_INT, normalized);
}

bool VertexAttribLayout::add_int(int32_t size, bool normalized) {
    return add_attrib(size, GL_INT, normalized);
}

bool VertexAttribLayout::add_byte(int32_t size, bool normalized) {
    return add_attrib(size, GL_BYTE, normalized);
}

bool VertexAttribLayout::add_unsigned_byte(int32_t size, bool normalized) {
    return add_attrib(size, GL_UNSIGNED_BYTE, normalized);
}

bool VertexAttribLayout::add_short(int32_t size, bool normalized) {
    return add_attrib(size, GL_SHORT, normalized);
}

bool VertexAttribLayout::add_unsigned_short(int32_t size, bool normalized) {
    return add_attrib(size, GL_UNSIGNED_SHORT, normalized);
}

VertexAttributes VertexAttribLayout::get(uint32_t i) const {
    return m_attrib[i];
}

uint32_t VertexAttribLayout::size() const {
    return m_attrib.size();
}

uint32_t VertexAttribLayout::stride() const {
    return m_stride;
}

}