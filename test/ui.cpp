#include "UI/Elements.hpp"
#include "UI/Renderer.hpp"
#include "UI/Menu.hpp"

#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Asset/AssetFactory.hpp"
#include "Asset/AssetManager.hpp"
#include "Text/FontSystem.hpp"
#include "Text/Font.hpp"
#include "Time/Timer.hpp"
#include "Graphic/Renderer.hpp"

#include "Graphic/PostProcessor.hpp"

void callback() {
    std::cout << "Button clicked" << std::endl;
}

int main(int argc, char* argv[]) {

    AMB::Window window(1000, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager;
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Logger& logger = AMB::Logger::instance();
    AMB::Renderer renderer;

    renderer.set_clear_color(0.02f, 0.1f, 0.2f, 1.0f);

    AMB::AssetHandle texture_handle = asset_factory.create_texture("test/res/Feather.png");
    if (!asset_manager.textures.validity(texture_handle)) {
        logger.log(AMB::Fatal, "Can not load texture");
        exit(EXIT_FAILURE);
    }
    AMB::Texture& texture = asset_manager.textures.get(texture_handle);

    AMB::AssetHandle font_handle = asset_factory.create_font("test/res/OpenSans.ttf", 26);
    if (!asset_manager.fonts.validity(font_handle)) {
        logger.log(AMB::Fatal, "Can not load font");
        exit(EXIT_FAILURE);
    }
    AMB::Font& font = asset_manager.fonts.get(font_handle);

    AMB::AssetHandle shader_handle = asset_factory.create_shader("test/res/ui.vert", "test/res/ui.frag");
    if (!asset_manager.shaders.validity(shader_handle)) {
        logger.log(AMB::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    AMB::Shader& shader = asset_manager.shaders.get(shader_handle);

    AMB::AssetHandle shader_pixel_handle = asset_factory.create_shader("test/res/post.vert", "test/res/pixelated.frag");
    if (!asset_manager.shaders.validity(shader_pixel_handle)) {
        logger.log(AMB::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    AMB::Shader& shader_pixel = asset_manager.shaders.get(shader_pixel_handle);
    shader_pixel.use_shader();
    shader_pixel.set_2f("u_resolution", mat::Vec2f{float(window.get_width()), float(window.get_height())});
    shader_pixel.set_1f("u_pixel_size", 4);

    AMB::AssetHandle shader_non_pixel_handle = asset_factory.create_shader("test/res/post.vert", "test/res/pixelated_not.frag");
    if (!asset_manager.shaders.validity(shader_non_pixel_handle)) {
        logger.log(AMB::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    AMB::Shader& shader_non_pixel = asset_manager.shaders.get(shader_non_pixel_handle);
    shader_non_pixel.use_shader();
    shader_non_pixel.set_2f("u_resolution", mat::Vec2f{float(window.get_width()), float(window.get_height())});
    shader_non_pixel.set_1f("u_pixel_size", 4);


    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), -1.0f, 1.0f);

    AMB::UI::UI_Renderer ui_renderer(shader, texture, font, 128);

    AMB::UI::UI_Factory factory;
    AMB::UI::UI_Menu ui_menu = factory
    .create_menu({0.0f, 0.0f}, {float(window.get_width()), float(window.get_height())})
    .begin_panel(AMB::UI::UI_ElementState::Normal, {50.0f, 50.0f}, AMB::UI::UI_PositionType::relative, {300.0f, 300.0f}, {0.6f, 0.6f, 0.6f, 1.0f}, AMB::UI::UI_Grid(3,3))
        .begin_text(AMB::UI::UI_ElementState::Normal, {1.0f, 2.0f}, AMB::UI::UI_PositionType::grid, {0.0f, 0.0f, 0.0f, 1.0f}, "Test of the UI System")
        .end()
        .begin_image(AMB::UI::UI_ElementState::Normal, {1.0f, 1.0f}, AMB::UI::UI_PositionType::grid, {90.0f, 90.0f}, {0.0f, 0.0f}, {1.0f, 1.0f})
        .end()
        .begin_panel(AMB::UI::UI_ElementState::Normal, {2.0f, 1.0f}, AMB::UI::UI_PositionType::grid, {90.0f, 25.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, AMB::UI::UI_Grid(1,1), AMB::UI::UI_Anchor::BL)
            .begin_button(AMB::UI::UI_ElementState::Normal, {0.0f, 0.0f}, AMB::UI::UI_PositionType::grid, {90.0f, 25.0f}, callback)
            .end()
        .end()
    .end()
    .complete_menu();

    ui_menu.submit(ui_renderer);
    ui_renderer.build_mesh();

    renderer.set_depth_test(false);
    renderer.set_blend(true);
   
    AMB::PostProcessor post_processor(window.get_width(), window.get_height());
    //post_processor.add_shader_effect(&shader_pixel);
    bool pixelized_post_processing = false;

    while (!event_manager.is_quitting())
    {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }
        if (event_manager.keyboard().key_down(AMB::KEY_CODE_SPACE)) {
            pixelized_post_processing = !pixelized_post_processing;
        }
        
        // Clear the screen
        renderer.clear();

        // Update
        ui_menu.update(event_manager);

        // Draw the triangle
        post_processor.begin();
        ui_renderer.draw(mvp);

        if (pixelized_post_processing) {
            post_processor.end(shader_pixel);
        }else{
            post_processor.end(shader_non_pixel);
        }

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();
    }
    

    std::cout << "Program completed" << std::endl;
    
    return 0;
}