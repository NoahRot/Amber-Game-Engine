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
#include "Particle/Particle2DSystem.hpp"

#include <random>

void update_part(AMB::Particle2D& p, float dt) {
    p.r -= 0.0004f*dt;
    p.g -= 0.0008f*dt;
    p.b -= 0.001f*dt;

    float cp = 0.95f;
    p.velocity *= cp;

    p.position += p.velocity * dt;
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

    AMB::Particle2DSystem particle_system;
    AMB::Particle2DRenderer particle_renderer(shader);

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    float dt = timer.get_delta_time();
    float acc = 0.0f;

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> position_dist_x(390.0f, 410.0f);
    std::uniform_real_distribution<float> position_dist_y(290.0f, 310.0f);
    std::uniform_real_distribution<float> velocity_dist(0.1f, 0.5f);
    std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * 3.14159265f);
    std::uniform_real_distribution<float> size_dist(3.0f, 6.0f);

    // Optional: disable depth test temporarily for debugging
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);


    while (!event_manager.is_quitting()) { 
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        
        // Clear the screen
        renderer.clear();

        // Update particles
        particle_system.update(dt, update_part);
        acc += dt;
        if (acc > 10) {
            acc = 0.0f;
            float angle = angle_dist(generator);
            float vel = velocity_dist(generator);

            AMB::Particle2D p;
            p.position = {position_dist_x(generator), position_dist_y(generator)};
            p.velocity = {std::cos(angle)*vel, std::sin(angle)*vel};
            p.r = 1.0f;
            p.g = 1.0f;
            p.b = 0.7f;
            p.a = 1.0f;
            p.size = size_dist(generator);
            p.life_time = 2000;

            particle_system.add_particle(p);
        }

        // Draw particles
        shader.set_mat4f("u_mvp", mvp); 
        particle_renderer.draw(particle_system);

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}