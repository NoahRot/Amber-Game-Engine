#include "Window/Window.hpp"
#include "Time/Timer.hpp"
#include "Event/Event.hpp"
#include "Asset/AssetManager.hpp"
#include "Asset/AssetFactory.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Renderer.hpp"
#include "Logger/Logger.hpp"

#include "Particle/Particle2D.hpp"
#include "Particle/Particle2DRenderer.hpp"
#include "Particle/Particle2DEmitter.hpp"

#include "Graphic/PostProcessor.hpp"

#include <random>

void update_part(AMB::Particle2DContext& p, float dt) {
    p.color[0] -= 0.0004f*dt;
    p.color[1] -= 0.0008f*dt;
    p.color[2] -= 0.001f*dt;

    float cp = 0.95f;
    p.velocity *= cp;

    p.position += p.velocity * dt;
}

void spawn(mat::Vec2f& position, mat::Vec2f& dimension, mat::Vec4f& color, mat::Vec2f& velocity, float& life_time) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> position_dist_x(390.0f, 410.0f);
    std::uniform_real_distribution<float> position_dist_y(290.0f, 310.0f);
    std::uniform_real_distribution<float> velocity_dist(0.1f, 0.5f);
    std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * 3.14159265f);
    std::uniform_real_distribution<float> size_dist(3.0f, 6.0f);

    float angle = angle_dist(generator);
    float vel = velocity_dist(generator);

    position = {position_dist_x(generator), position_dist_y(generator)};
    velocity = {std::cos(angle)*vel, std::sin(angle)*vel};
    color[0] = 1.0f;
    color[1] = 1.0f;
    color[2] = 0.7f;
    color[3] = 1.0f;
    dimension = size_dist(generator);
    life_time = 2000;
}

void update_part_2(AMB::Particle2DContext& p, float dt) {
    p.color[0] -= 0.001f*dt;
    p.color[1] -= 0.0008f*dt;
    p.color[2] -= 0.0003f*dt;
}

void spawn_2(mat::Vec2f& position, mat::Vec2f& dimension, mat::Vec4f& color, mat::Vec2f& velocity, float& life_time) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> angle(0.0f, 2.0f*M_PI);
    std::uniform_real_distribution<float> radii(0.0f, 100.0f);
    std::uniform_real_distribution<float> size_dist(3.0f, 6.0f);
    
    float radius = radii(generator);
    float a0 = angle(generator);

    position = {400.0f + radius*cosf(a0), 300.0f + radius*sinf(a0)};
    velocity = {0.0f, 0.0f};
    color[0] = 0.7f;
    color[1] = 1.0f;
    color[2] = 1.0f;
    color[3] = 1.0f;
    dimension = size_dist(generator);
    life_time = 2000;
}

int main(int argc, char* argv[]) { 

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager; 
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;
    AMB::Logger& logger = AMB::Logger::instance();

    AMB::AssetHandle shader_handle = asset_factory.create_shader(std::string("test/res/Particle.vert"), std::string("test/res/Particle.frag"));
    if (!asset_manager.shaders.validity(shader_handle)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }

    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);
    
    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), -1.0f, 1.0f);

    //AMB::Particle2DSystem particle_system;
    AMB::Emitter2D emitter(10, spawn_2, update_part_2, 10);
    AMB::Particle2DRenderer particle_renderer(shader);
    particle_renderer.add_emitter(&emitter);

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    float dt = timer.get_delta_time();
    float acc = 0.0f;

    // Pixelated shader
    AMB::AssetHandle shader_pp = asset_factory.create_shader(std::string("test/res/post.vert"), std::string("test/res/pixelated.frag"));
    if (!asset_manager.shaders.validity(shader_pp)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }
    AMB::Shader& shader_pixel = asset_manager.shaders.get(shader_pp);
    shader_pixel.use_shader();
    shader_pixel.set_2f("u_resolution", mat::Vec2f{float(window.get_width()), float(window.get_height())});
    shader_pixel.set_1f("u_pixel_size", 4.0f);

    // Blur shader
    AMB::AssetHandle shader_pp1 = asset_factory.create_shader(std::string("test/res/post.vert"), std::string("test/res/blur.frag"));
    if (!asset_manager.shaders.validity(shader_pp1)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }
    AMB::Shader& shader_blur = asset_manager.shaders.get(shader_pp1);
    shader_blur.use_shader();
    shader_blur.set_2f("u_texel_size", mat::Vec2f{1.0f/float(window.get_width()), float(1.0f/window.get_height())});
    shader_blur.set_1i("u_horizontal", true);

    // Bright shader
    AMB::AssetHandle shader_pp2 = asset_factory.create_shader(std::string("test/res/post.vert"), std::string("test/res/bright.frag"));
    if (!asset_manager.shaders.validity(shader_pp2)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }
    AMB::Shader& shader_bright = asset_manager.shaders.get(shader_pp2);
    shader_bright.use_shader();
    shader_bright.set_1f("u_threshold", 0.5f);

    // Bloom shader
    AMB::AssetHandle shader_pp3 = asset_factory.create_shader(std::string("test/res/post.vert"), std::string("test/res/bloom.frag"));
    if (!asset_manager.shaders.validity(shader_pp3)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }
    AMB::Shader& shader_bloom = asset_manager.shaders.get(shader_pp3);
    shader_bloom.use_shader();
    shader_bloom.set_1f("u_bloom_intensity", 5.0f);

    AMB::PostProcessor pp(window.get_width(), window.get_height());
    pp.add_shader_effect(&shader_bright);
    pp.add_shader_effect(&shader_blur);

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        
        // Clear the screen
        renderer.clear();

        // Update particles
        //particle_system.update(dt, update_part);
        emitter.update(dt);

        // Draw particles

        shader.set_mat4f("u_mvp", mvp); 
        particle_renderer.update();

        pp.begin();

        // Draw particles to scene FBO
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        particle_renderer.draw(mvp);

        pp.end(shader_bloom, AMB::PostProcessMode::multiple); // “do nothing” shader, just output the FBO

        // Restore states if needed
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        // Present the frame
        window.present();

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}