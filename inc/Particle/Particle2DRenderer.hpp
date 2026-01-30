#pragma once

#include "Graphic/Shader.hpp"
#include "Particle/Particle2DEmitter.hpp"

namespace AMB {

class Particle2DRenderer {
public:
	Particle2DRenderer(Shader& shader);

	void add_emitter(Emitter2D* emitter);

	void update();

	void draw(const mat::Mat4f& mvp);
	
private:
	void resize_index();

	std::vector<Particle2DVertex> m_vertex;
	std::vector<uint32_t> m_index;
    uint32_t m_size;

	std::vector<Emitter2D*> m_emitters;

    VertexAttribLayout m_layout;
    std::shared_ptr<VertexBuffer> m_vbo;
	std::shared_ptr<IndexBuffer> m_ibo;
    std::shared_ptr<VertexArray> m_vao;
	Shader& m_shader;
};

}