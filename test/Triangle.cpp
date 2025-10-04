#include "Window/Window.hpp"
#include "Time/Timer.hpp"
#include "Event/Event.hpp"
#include "Asset/AssetManager.hpp"
#include "Asset/AssetFactory.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/VertexArray.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager;
    AMB::AssetFactory asset_factory(asset_manager);

    AMB::AssetHandle shader_handle = asset_factory.create_shader(std::string("test/res/Color.vert"), std::string("test/res/Color.frag"));
    if (!asset_manager.shaders.validity(shader_handle)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }

    std::vector<float> vertices = { 
        // Positions            // Colors
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f, // Top vertex (Red)
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f, // Bottom right vertex (Green)
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f  // Bottom left vertex (Blue)
    };
    std::vector<uint32_t> indices = { 0, 1, 2 };

    std::shared_ptr<AMB::VertexBuffer> vbo_ptr = std::make_shared<AMB::VertexBuffer>(vertices.data(), vertices.size() * sizeof(float), true);
    std::shared_ptr<AMB::IndexBuffer> ibo_ptr = std::make_shared<AMB::IndexBuffer>(indices.data(), indices.size(), true);
    AMB::VertexAttribLayout layout;
    layout.add_float(3, false); // Position attribute (3 floats)
    layout.add_float(4, false); // Color attribute (4 floats)

    AMB::VertexArray vao;
    vao.add_vertex_buffer(vbo_ptr, layout);
    vao.set_index_buffer(ibo_ptr);

    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);
    shader.use_shader();

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        
        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        vao.bind();
        ibo_ptr->bind();
        shader.use_shader();
        glDrawElements(GL_TRIANGLES, ibo_ptr->count(), GL_UNSIGNED_INT, nullptr);

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}