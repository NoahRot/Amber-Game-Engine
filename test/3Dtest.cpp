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

#include "Camera/Camera3D.hpp"

#include <random>
#include <chrono>

struct Vertex {
    float x, y, z;
    float r, g, b;
};

int main(int argc, char* argv[]) { 

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager; 
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;
    AMB::Logger& logger = AMB::Logger::instance();

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_cull_face(true);

    mat::Quatf orientation = mat::euler_angle_to_quat<float>(0.0f, 0.0f, 0.0f);
    AMB::CameraPerspective camera(mat::Vec3f{0.0f, 0.0f, 0.0f}, orientation, float(window.get_width())/float(window.get_height()), M_PI/3.0f, 10.0f, 100.0f);

    AMB::AssetHandle shader_handle = asset_factory.create_shader("test/res/3D.vert", "test/res/3D.frag");
    if (!asset_manager.shaders.validity(shader_handle)) {
        logger.log(AMB::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }else{
        logger.log(AMB::Info, "Shader loaded");
    }
    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);

    AMB::VertexAttribLayout layout;
    layout.add_float(3); // Position
    layout.add_float(3); // Color

    float cote = 30.0f;
    float h = cote * 0.5f;

    std::vector<Vertex> vertices = {
        {-h, -h, -h, 1, 0, 0},
        { h, -h, -h, 0, 1, 0},
        { h,  h, -h, 0, 0, 1},
        {-h,  h, -h, 1, 1, 0},

        {-h, -h,  h, 1, 0, 1},
        { h, -h,  h, 0, 1, 1},
        { h,  h,  h, 1, 1, 1},
        {-h,  h,  h, 0, 0, 0}
    };
    std::vector<uint32_t> indices = {
        // Front (+Z)
        4, 6, 5,
        6, 4, 7,
        //ck  Ba(-Z)
        1, 3, 0,
        3, 1, 2,
        //ft  Le(-X)
        0, 7, 4,
        7, 0, 3,
        //ght Ri (+X)
        5, 2, 1,
        2, 5, 6,
        //p ( To+Y)
        3, 6, 7,
        6, 3, 2,
        //tto Bom (-Y)
        0, 5, 1,
        5, 0, 4
    };

    std::shared_ptr<AMB::VertexBuffer> vbo = AMB::create_vertex_buffer<Vertex>(vertices, true);
    std::shared_ptr<AMB::IndexBuffer> ibo = AMB::create_index_buffer(indices, true);
    std::shared_ptr<AMB::VertexArray> vao = AMB::create_vertex_array();
    vao->add_vertex_buffer(vbo, layout);
    vao->set_index_buffer(ibo);

    float angle_a(0.0f), angle_a_vel(0.01f);
    float angle_b(0.0f), angle_b_vel(0.007f);

    mat::Vec3f cube_position{0.0f, 0.0f, -70.0f};

    while (!event_manager.is_quitting()) {

        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        float camera_vel = 2.0f;
        float camera_angle = 0.01f;
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_W)) {
            camera.move({0.0f, 0.0f, -camera_vel});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_S)) {
            camera.move({0.0f, 0.0f, camera_vel});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_A)) {
            camera.move({-camera_vel, 0.0f, 0.0f});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_D)) {
            camera.move({camera_vel, 0.0f, 0.0f});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_Q)) {
            camera.rotate(0.0f, 0.0f, camera_angle);
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_E)) {
            camera.rotate(0.0f, 0.0f, -camera_angle);
        }

        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_RETURN)) {
            camera.set_orientation(cube_position, mat::Vec3f{0.0f, 1.0f, 0.0f});
        }

        // Clear the screen
        renderer.clear();

        angle_a += angle_a_vel;
        angle_b += angle_b_vel;

        // Update camera
        mat::Mat4f vp = camera.get_vp();
        mat::Mat4f m = mat::dot(mat::translate3<float>(cube_position), mat::dot(mat::rotateY<float>(angle_a), mat::rotateX<float>(angle_b)));

        // Draw
        shader.set_mat4f("u_mvp", mat::dot(vp, m));
        renderer.draw_arrays(vao, shader);

        // Present the frame
        window.present();

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}