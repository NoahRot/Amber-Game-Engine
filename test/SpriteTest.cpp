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
#include "Sprite/Sprite.hpp"
#include "Sprite/SpriteFactory.hpp"
#include "Sprite/SpriteSheet.hpp"
#include "Sprite/SpriteRenderer.hpp"
#include "Sprite/SpriteBatchRenderer.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager; 
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;
    AMB::Logger& logger = AMB::Logger::instance();

    AMB::AssetHandle shader_handle = asset_factory.create_shader(std::string("test/res/sprite.vert"), std::string("test/res/sprite.frag"));
    if (!asset_manager.shaders.validity(shader_handle)) {
        std::cerr << "Failed to add shader asset." << std::endl;
        return EXIT_FAILURE; 
    }else{
        std::cout << "Shader loaded successfully." << std::endl;
    }

    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);

    AMB::AssetHandle texture_handle = asset_factory.create_texture(std::string("test/res/fruit.png"));
    if (!asset_manager.textures.validity(texture_handle)) {
        std::cerr << "Failed to add texture asset." << std::endl;
        return EXIT_FAILURE;
    }else{
        std::cout << "Texture loaded successfully." << std::endl;
    }

    AMB::SpriteFactory sprite_factory(asset_manager);

    AMB::Sprite sprite = sprite_factory.create_single_texture_sprite(texture_handle, {100.0f, 25.0f, 0.0f}, {100.0f, 100.0f}, {0.0f, 0.0f}, {1.0f, 1.0f});
    AMB::SpriteSheet sprite_sheet = sprite_factory.create_sprite_sheet_quad(texture_handle, {16, 16}, {64.0f, 64.0f});
    AMB::SpriteRenderer sprite_renderer(asset_manager, shader);

    AMB::SpriteBatchRenderer sprite_batch(asset_manager, shader, texture_handle, 2048);

    AMB::Sprite sprite_i = sprite_sheet.get_sprite(0);
    uint32_t current_sprite_i = 0;

    AMB::SpriteAnimation animation = sprite_factory.create_animation(sprite_sheet, 0, 2, 300.0f);
    
    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), -1.0f, 1.0f);

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    float dt = timer.get_delta_time();

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        /*if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_SPACE)) {
            current_sprite_i++;
            if (current_sprite_i >= sprite_sheet.size()) {
                current_sprite_i = 0;
            }
            sprite_i = sprite_sheet.get_sprite(current_sprite_i); 

            std::cout << "Sprite info :" 
            "\n + sprite index " << current_sprite_i <<
            "\n + texture coord" << sprite_i.get_texture_coord() <<
            "\n + texture dim" << sprite_i.get_texture_dim() << std::endl;
        }*/

        animation.update(dt);
        sprite_i = animation.get_current_sprite();
        sprite_batch.reset();
        sprite_batch.submit_sprite(sprite_i);
        sprite_batch.submit_sprite(sprite);
        sprite_batch.build_mesh();
        
        // Clear the screen
        renderer.clear();

        // Draw sprite
        sprite_renderer.change_sprite(sprite_i); 
        //sprite_renderer.draw(mvp); 
        sprite_batch.draw(mvp);

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}