#include "Graphic/Renderer.hpp"

namespace AMB {

Renderer::Renderer() {
    set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    set_depth_test(true);
    set_blend(true);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::set_depth_test(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }else{
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::set_blend(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glDisable(GL_BLEND);
    }
}

void Renderer::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
    glViewport(x, y, width, height);
}

void Renderer::draw_arrays(std::shared_ptr<VertexArray> vao, Shader& shader) {
    vao->bind();
    shader.use_shader();
    std::shared_ptr<IndexBuffer> ibo_ptr = vao->get_index_buffer();
    ibo_ptr->bind();
    glDrawElements(GL_TRIANGLES, ibo_ptr->count(), GL_UNSIGNED_INT, nullptr);
}

}