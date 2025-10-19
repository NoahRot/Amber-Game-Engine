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
#include "Text/FontSystem.hpp"
#include "Text/Font.hpp"
#include "Text/Text.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(1000, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager;
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(false);

    AMB::AssetHandle shader_handle = asset_factory.create_shader(std::string("test/res/Text.vert"), std::string("test/res/Text.frag"));
    if (!asset_manager.shaders.validity(shader_handle)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }

    AMB::AssetHandle font_handle = asset_factory.create_font(std::string("test/res/OpenSans.ttf"), 16);
    if (!asset_manager.fonts.validity(font_handle)) {
        std::cerr << "Failed to add font asset." << std::endl;
        return EXIT_FAILURE;
    }else{
        std::cout << "Font loaded successfully." << std::endl;
    }

    struct Vertex {
        float x, y, z;  // Position
        float r, g, b, a;  // Color
        float u, v;     // Texture coordinates
    };

    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);
    shader.use_shader();
    AMB::Font& font = asset_manager.fonts.get(font_handle);
    AMB::Texture& texture = font.get_texture(); 
    texture.bind(0);

    mat::Mat4f ortho = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), -1.0f, 1.0f);

    AMB::TextRenderer text_renderer(font, shader, 1.0f, 1.0f, 1.0f, 30); 
    text_renderer.submit_text("Hello World!\nThis is a text rendering test.\n0123456789", 
        mat::Vec3f({25.0f, 500.0f, 0.0f}), 1.0f, 1.0f, 0.0f, 1.0f);
    text_renderer.build_mesh(); 

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit(); 
        }

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_SPACE)) {

            text_renderer.reset();
            text_renderer.submit_text("The quick brown fox jumps over the lazy dog.\n"
                                      "Pack my box with five dozen liquor jugs.\n"
                                      "Sphinx of black quartz, judge my vow.\n"
                                      "How vexingly quick daft zebras jump!\n"
                                      "Bright vixens jump; dozy fowl quack.\n"
                                      "Jackdaws love my big sphinx of quartz.\n"
                                      "The five boxing wizards jump quickly.\n"
                                      "Quick zephyrs blow, vexing daft Jim.\n"
                                      "Two driven jocks help fax my big quiz.\n"
                                      "Five quacking zephyrs jolt my wax bed.\n",
                                      mat::Vec3f({25.0f, 500.0f, 0.0f}), 1.0f, 1.0f, 0.0f, 1.0f);
            text_renderer.build_mesh();
        }
        
        // Clear the screen
        renderer.clear(); 

        // Draw the text
        text_renderer.draw(ortho); 

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}