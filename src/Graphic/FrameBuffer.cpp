#include "Graphic/FrameBuffer.hpp"

namespace AMB{

FrameBuffer::FrameBuffer(int width, int height) 
: m_width(width), m_height(height)
{
    reset();
}

FrameBuffer::~FrameBuffer() {
    if (m_fbo)              { glDeleteFramebuffers(1, &m_fbo); }
    if (m_color_texture)    { glDeleteTextures(1, &m_color_texture); }
    if (m_rbo)              { glDeleteRenderbuffers(1, &m_rbo); }
}

void FrameBuffer::reset() {
    if (m_fbo) {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures(1, &m_color_texture);
        glDeleteRenderbuffers(1, &m_rbo);
    }

    // Generate framebuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Generate texture
    glGenTextures(1, &m_color_texture);
    glBindTexture(GL_TEXTURE_2D, m_color_texture);

    // Create texture 2D
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        m_width,
        m_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    // Set paramters of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Attach the texture
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        m_color_texture,
        0
    );

    // Generate renderbuffer !!! NEED TO DISABLE DEPTH TEST !!!
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);

    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        m_width,
        m_height
    );

    // Attach renderbuffer
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        m_rbo
    );

    // Tell OpenGL which color buffers to draw into
    GLenum buffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buffers);

    // Check validity
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Logger::instance().log(Error, "Unvalid FrameBuffer");
    }

    unbind();
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t FrameBuffer::get_color_texture() const {
    return m_color_texture;
}

}