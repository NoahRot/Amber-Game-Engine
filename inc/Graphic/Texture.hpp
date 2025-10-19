#pragma once

#include <glad/glad.h>

#include <inttypes.h>

#include "Logger/Logger.hpp"

namespace AMB {

enum class TextureFilter {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

enum class TextureWrap {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

class Texture {
public:
    Texture(uint32_t texture_id, int32_t width, int32_t height, int32_t bpp);

    ~Texture();

    int32_t get_height() const;

    int32_t get_width() const;

    void bind(int32_t slot = 0);

    void unbind();

    void set_filter(TextureFilter filter_min, TextureFilter filter_mag);

    void set_wrap(TextureWrap wrap_s, TextureWrap wrap_t);

    static void set_default_filter(TextureFilter filter_min, TextureFilter filter_mag);

    static void set_default_wrap(TextureWrap wrap_s, TextureWrap wrap_t);

    void update_data(const void* data) {
        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,               // mipmap level
            0, 0,            // offset
            m_width,
            m_height,
            GL_RGBA,         // format (matches creation)
            GL_UNSIGNED_BYTE,// type (matches creation)
            data             // pointer to CPU memory with pixels
        );
    }

    void update_data(const void* data, uint32_t format, uint32_t data_type) {
        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,               // mipmap level
            0, 0,            // offset
            m_width,
            m_height,
            format,         // format (matches creation)
            data_type,      // type (matches creation)
            data             // pointer to CPU memory with pixels
        );
    }

private:
    uint32_t m_texture_id;
    int32_t m_width;
    int32_t m_height;
    int32_t m_bpp;

    static TextureFilter s_default_filter_min;
    static TextureFilter s_default_filter_mag;
    static TextureWrap s_default_wrap_s;
    static TextureWrap s_default_wrap_t;
};

}