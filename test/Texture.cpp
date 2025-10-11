#include "Window/Window.hpp"
#include "Time/Timer.hpp"
#include "Event/Event.hpp"
#include "Asset/AssetManager.hpp"
#include "Asset/AssetFactory.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/Renderer.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager;
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;

    AMB::AssetHandle shader_handle = asset_factory.create_shader(std::string("test/res/triangle.vert"), std::string("test/res/triangle.frag"));
    if (!asset_manager.shaders.validity(shader_handle)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }

    AMB::AssetHandle texture_handle = asset_factory.create_texture(std::string("test/res/Feather.png"));
    if (!asset_manager.textures.validity(texture_handle)) {
        std::cerr << "Failed to add texture asset." << std::endl;
        return EXIT_FAILURE;
    }else{
        std::cout << "Texture loaded successfully." << std::endl;
    }

    AMB::AssetHandle empty_texture_handle = asset_factory.create_texture(100, 100, 120, 180, 200, 255);
    if (!asset_manager.textures.validity(empty_texture_handle)) {
        std::cerr << "Failed to add empty texture asset." << std::endl;
        return EXIT_FAILURE;
    }else{
        std::cout << "Empty texture created successfully." << std::endl;
    }

    struct Vertex {
        float x, y, z;  // Position
        float r, g, b, a;  // Color
        float u, v;     // Texture coordinates
    };

    std::vector<Vertex> vertices = { 
        Vertex{-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f}, // Bottom left vertex (Red)
        Vertex{ 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f}, // Bottom right vertex (Green)
        Vertex{ 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f}, // Top right vertex (Blue)
        Vertex{-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f}  // Top left vertex (White)
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    std::shared_ptr<AMB::VertexBuffer> vbo_ptr = AMB::create_vertex_buffer(vertices, true);
    std::shared_ptr<AMB::IndexBuffer> ibo_ptr = AMB::create_index_buffer(indices, true);
    AMB::VertexAttribLayout layout;
    layout.add_float(3, false); // Position attribute (3 floats)
    layout.add_float(4, false); // Color attribute (3 floats)
    layout.add_float(2, false); // Texture coordinate attribute (2 floats)

    std::shared_ptr<AMB::VertexArray> vao_ptr = AMB::create_vertex_array();
    vao_ptr->add_vertex_buffer(vbo_ptr, layout);
    vao_ptr->set_index_buffer(ibo_ptr);

    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);
    shader.use_shader();
    AMB::Texture& texture = asset_manager.textures.get(texture_handle);
    texture.bind(0); 
    AMB::Texture& empty_texture = asset_manager.textures.get(empty_texture_handle);
    empty_texture.bind(0);

    texture.set_filter(AMB::TextureFilter::LINEAR, AMB::TextureFilter::LINEAR);

    mat::Mat4f mvp = mat::identity<float, 4>();

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        
        // Clear the screen
        renderer.clear();

        // Draw the triangle
        texture.bind(0);
        //empty_texture.bind(0);
        shader.set_mat4f("u_mvp", mvp);
        renderer.draw_arrays(vao_ptr, shader);

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}