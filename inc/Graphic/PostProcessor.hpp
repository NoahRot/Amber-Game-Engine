#pragma once

#include <inttypes.h>
#include <memory>

#include "Graphic/FrameBuffer.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

#include "Asset/AssetHandle.hpp"
#include "Asset/AssetManager.hpp"
#include "Asset/AssetFactory.hpp"

namespace AMB {

struct PostProcessorVertex {
    float x, y;
    float u, v;
};

enum class PostProcessMode {
    single,
    multiple
};

struct PostProcessEffects {
    Shader* shader;
    PostProcessMode mode;
    bool scene_modifier;
};

class PostProcessor {
public:
    PostProcessor(uint32_t width, uint32_t height, AssetManager& asset_manager, AssetFactory& asset_factory);

    void begin();

    void add_effect(Shader* shader, PostProcessMode mode, bool scene_modifier);

    void clear_effect();

    void end();

private:
    void draw_full_screen_quad();

    FrameBuffer m_scene_fbo;
    FrameBuffer m_pingpong_fbo[2];

    std::vector<PostProcessEffects> m_effects;
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;

    Shader* m_final_shader;

    int m_width, m_height;
};

}