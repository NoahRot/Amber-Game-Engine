#include "Graphic/Texture.hpp"

namespace AMB {

TextureFilter Texture::s_default_filter_min = TextureFilter::NEAREST;
TextureFilter Texture::s_default_filter_mag = TextureFilter::NEAREST;
TextureWrap Texture::s_default_wrap_s = TextureWrap::CLAMP_TO_EDGE;
TextureWrap Texture::s_default_wrap_t = TextureWrap::CLAMP_TO_EDGE;

Texture::Texture(uint32_t texture_id, int32_t width, int32_t height, int32_t bpp)
: m_texture_id(texture_id), m_width(width), m_height(height), m_bpp(bpp)
{
    set_filter(s_default_filter_min, s_default_filter_mag);
    set_wrap(s_default_wrap_s, s_default_wrap_t);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture_id);
}

int32_t Texture::get_height() const { 
    return m_height; 
}

int32_t Texture::get_width() const { 
    return m_width; 
}

void Texture::bind(int32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::set_filter(TextureFilter filter_min, TextureFilter filter_mag) {
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    GLenum gl_min, gl_mag;

    switch (filter_min) {
        case TextureFilter::NEAREST: gl_min = GL_NEAREST; break;
        case TextureFilter::LINEAR: gl_min = GL_LINEAR; break;
        case TextureFilter::NEAREST_MIPMAP_NEAREST: gl_min = GL_NEAREST_MIPMAP_NEAREST; break;
        case TextureFilter::LINEAR_MIPMAP_NEAREST: gl_min = GL_LINEAR_MIPMAP_NEAREST; break;
        case TextureFilter::NEAREST_MIPMAP_LINEAR: gl_min = GL_NEAREST_MIPMAP_LINEAR; break;
        case TextureFilter::LINEAR_MIPMAP_LINEAR: gl_min = GL_LINEAR_MIPMAP_LINEAR; break;
        default: gl_min = GL_LINEAR; break;
    }

    switch (filter_mag) {
        case TextureFilter::NEAREST: gl_mag = GL_NEAREST; break;
        case TextureFilter::LINEAR: gl_mag = GL_LINEAR; break;
        // MAG_FILTER only supports NEAREST and LINEAR
        default: gl_mag = GL_LINEAR; break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag);
}

void Texture::set_wrap(TextureWrap wrap_s, TextureWrap wrap_t) {
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    GLenum gl_wrap_s, gl_wrap_t;

    switch (wrap_s) {
        case TextureWrap::REPEAT: gl_wrap_s = GL_REPEAT; break;
        case TextureWrap::MIRRORED_REPEAT: gl_wrap_s = GL_MIRRORED_REPEAT; break;
        case TextureWrap::CLAMP_TO_EDGE: gl_wrap_s = GL_CLAMP_TO_EDGE; break;
        case TextureWrap::CLAMP_TO_BORDER: gl_wrap_s = GL_CLAMP_TO_BORDER; break;
        default: gl_wrap_s = GL_REPEAT; break;
    }

    switch (wrap_t) {
        case TextureWrap::REPEAT: gl_wrap_t = GL_REPEAT; break;
        case TextureWrap::MIRRORED_REPEAT: gl_wrap_t = GL_MIRRORED_REPEAT; break;
        case TextureWrap::CLAMP_TO_EDGE: gl_wrap_t = GL_CLAMP_TO_EDGE; break;
        case TextureWrap::CLAMP_TO_BORDER: gl_wrap_t = GL_CLAMP_TO_BORDER; break;
        default: gl_wrap_t = GL_REPEAT; break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap_t);
}

void Texture::set_default_filter(TextureFilter filter_min, TextureFilter filter_mag) {
    s_default_filter_min = filter_min;
    s_default_filter_mag = filter_mag;
}

void Texture::set_default_wrap(TextureWrap wrap_s, TextureWrap wrap_t) {
    s_default_wrap_s = wrap_s;
    s_default_wrap_t = wrap_t;
}

}