#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>
#include <glad/glad.h>

namespace AMB {

struct VertexAttributes {
    /// @brief The size of the attribute (1,2,3 or 4)
    int32_t size;

    /// @brief The type of variable
    uint32_t type;

    /// @brief If the parameters should be normalized
    bool normalized;

    /// @brief Stride of the attribute in bytes
    uint32_t stride;
};

uint32_t get_gl_enum_stride(uint32_t type);

class VertexAttribLayout {
public:
    VertexAttribLayout();

    bool add_attrib(int32_t size, GLenum type, bool normalized = false);

    bool add_float(int32_t size, bool normalized = false);

    bool add_unsigned_int(int32_t size, bool normalized = false);

    bool add_int(int32_t size, bool normalized = false);

    bool add_byte(int32_t size, bool normalized = false);

    bool add_unsigned_byte(int32_t size, bool normalized = false);

    bool add_short(int32_t size, bool normalized = false);

    bool add_unsigned_short(int32_t size, bool normalized = false);

    VertexAttributes get(uint32_t i) const;

    uint32_t size() const;

    uint32_t stride() const;

private:
    std::vector<VertexAttributes> m_attrib;
    uint32_t m_stride;
};

}