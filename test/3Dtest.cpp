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
#include "Camera/Camera2D.hpp"
#include "UI/Renderer.hpp"
#include "UI/Menu.hpp"

#include <random>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

struct Vertex {
    float x, y, z;
    float r, g, b;
};

uint32_t get_midpoint(uint32_t a, uint32_t b, float radii, std::vector<Vertex>& vertices, std::unordered_map<uint64_t, uint32_t>& map_side_index) {
    uint64_t key = (uint64_t)std::min(a, b) << 32 | std::max(a, b);

    std::unordered_map<uint64_t, uint32_t>::iterator it = map_side_index.find(key);
    if (it != map_side_index.end()) {
        return it->second;

    }else{
        Vertex& v1 = vertices[a];
        Vertex& v2 = vertices[b];
        
        uint32_t id = vertices.size();
        mat::Vec3f point{
            0.5f*(v1.x + v2.x),
            0.5f*(v1.y + v2.y),
            0.5f*(v1.z + v2.z)
        };
        point = mat::normalize(point) * radii;

        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        vertices.push_back(Vertex{
            point[0], point[1], point[2],
            dist(generator), dist(generator), dist(generator)
        });
        map_side_index[key] = id;
        return id;
    }
}

void generate_points(float radii, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    uint32_t nbr_triangles = indices.size()/3;
    std::unordered_map<uint64_t, uint32_t> map_side_index;
    std::vector<uint32_t> new_indices;

    // Treat each face
    for (uint32_t i(0) ; i < nbr_triangles ; ++i) {
        // Get mid points
        uint32_t i0 = i * 3 + 0;
        uint32_t i1 = i * 3 + 1;
        uint32_t i2 = i * 3 + 2;

        uint32_t v0 = indices[i0];
        uint32_t v1 = indices[i1];
        uint32_t v2 = indices[i2];

        uint32_t id_01 = get_midpoint(v0, v1, radii, vertices, map_side_index);
        uint32_t id_12 = get_midpoint(v1, v2, radii, vertices, map_side_index);
        uint32_t id_20 = get_midpoint(v2, v0, radii, vertices, map_side_index);

        new_indices.insert(new_indices.end(), {
            v0,    id_01, id_20,
            id_01, v1,    id_12,
            id_20, id_12, v2,
            id_01, id_12, id_20
        });

    }

    indices = std::move(new_indices);
}

void create_icosahedron(float radius,
                        std::vector<Vertex>& vertices,
                        std::vector<uint32_t>& indices,
                        uint32_t nbr_iteration = 0)
{
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

    std::vector<mat::Vec3f> pos = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    vertices.clear();
    for (auto& p : pos) {
        p.normalize();
        p *= radius;
        vertices.push_back({ p[0], p[1], p[2], dist(generator), dist(generator), dist(generator) });
    }

    indices = {
        11,0,5, 5,0,1,  1,0,7,   7,0,10, 10,0,11,
        5,1,9,  11,5,4, 10,11,2, 7,10,6, 1,7,8,
        9,3,4,  4,3,2,  2,3,6,   6,3,8,  8,3,9,
        9,4,5,  4,2,11, 2,6,10,  6,8,7,  8,9,1
    };

    for (uint32_t i(0) ; i < nbr_iteration ; ++i) {
        generate_points(radius, vertices, indices);
    }
}

void button_increase() {
    std::cout << "INCREASE" << std::endl;
}

void button_decrease() {
    std::cout << "DECREASE" << std::endl;
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

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_cull_face(true);

    mat::Quatf orientation = mat::euler_angle_to_quat<float>(0.0f, 0.0f, 0.0f);
    AMB::CameraPerspective camera(mat::Vec3f{0.0f, 0.0f, 0.0f}, orientation, float(window.get_width())/float(window.get_height()), M_PI/3.0f, 10.0f, 500.0f);
    AMB::CameraOrthographic camera2D(mat::Vec2f{0.0f, 0.0f}, mat::Vec2f{float(window.get_width()), float(window.get_height())}, 0.0f);

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

    create_icosahedron(30.0f, vertices, indices);

    std::shared_ptr<AMB::VertexBuffer> vbo = AMB::create_vertex_buffer<Vertex>(vertices, true);
    std::shared_ptr<AMB::IndexBuffer> ibo = AMB::create_index_buffer(indices, true);
    std::shared_ptr<AMB::VertexArray> vao = AMB::create_vertex_array();
    vao->add_vertex_buffer(vbo, layout);
    vao->set_index_buffer(ibo);

    float angle_a(0.0f), angle_a_vel(0.01f);
    float angle_b(0.0f), angle_b_vel(0.007f);

    mat::Vec3f cube_position{0.0f, 0.0f, -70.0f};

    AMB::AssetHandle shader_ui_handle = asset_factory.create_shader("test/res/ui.vert", "test/res/ui.frag");
    if (!asset_manager.shaders.validity(shader_ui_handle)) {
        logger.log(AMB::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }else{
        logger.log(AMB::Info, "Shader loaded");
    }
    AMB::Shader& shader_ui = asset_manager.shaders.get(shader_ui_handle);

    AMB::AssetHandle texture_handle = asset_factory.create_texture("test/res/Feather.png");
    if (!asset_manager.textures.validity(texture_handle)) {
        logger.log(AMB::Fatal, "Can not load texture");
        exit(EXIT_FAILURE);
    }else{
        logger.log(AMB::Info, "texture loaded");
    }
    AMB::Texture& texture = asset_manager.textures.get(texture_handle);

    AMB::AssetHandle font_handle = asset_factory.create_font("test/res/OpenSans.ttf", 30);
    if (!asset_manager.fonts.validity(font_handle)) {
        logger.log(AMB::Fatal, "Can not load font");
        exit(EXIT_FAILURE);
    }else{
        logger.log(AMB::Info, "font loaded");
    }
    AMB::Font& font = asset_manager.fonts.get(font_handle);

    AMB::UI::UI_Renderer ui_renderer(float(window.get_width()), float(window.get_height()), shader_ui, texture, font, 32);
    AMB::UI::UI_Factory ui_factory;
    AMB::UI::UI_Menu menu = ui_factory
    .create_menu(mat::Vec2f{0.0f, 0.0f}, mat::Vec2f{float(window.get_width()), float(window.get_height())}, AMB::UI::UI_Grid())
    .begin_panel(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 0.0f}, AMB::UI::UI_PositionType::relative, mat::Vec2f{300.0f, 300.0f}, mat::Vec4f{0.01f, 0.1f, 0.3f, 1.0f}, AMB::UI::UI_Grid(3, 3))
        .begin_panel(AMB::UI::UI_ElementState::Normal, mat::Vec2f{1.0f, 1.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{90.0f, 30.0f}, mat::Vec4f{0.8f, 0.8f, 0.8f, 1.0f})
        .end()
        .begin_text(AMB::UI::UI_ElementState::Normal, mat::Vec2f{1.0f, 2.0f}, AMB::UI::UI_PositionType::grid, mat::Vec4f{1.0f, 1.0f, 1.0f, 1.0f}, "Icosphere")
        .end()
        .begin_panel(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 1.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{100.0f, 100.0f}, mat::Vec4f{0.0f, 0.0f, 0.0f, 0.0f}, AMB::UI::UI_Grid(2, 1))
            .begin_panel(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 1.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{90.0f, 30.0f}, mat::Vec4f{0.0f, 1.0f, 0.0f, 1.0f}, AMB::UI::UI_Grid(1, 1))
                .begin_button(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 0.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{90.0f, 30.0f}, button_increase)
                .end()
            .end()
            .begin_panel(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 0.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{90.0f, 30.0f}, mat::Vec4f{1.0f, 0.0f, 0.0f, 1.0f}, AMB::UI::UI_Grid(1, 1))
                .begin_button(AMB::UI::UI_ElementState::Normal, mat::Vec2f{0.0f, 0.0f}, AMB::UI::UI_PositionType::grid, mat::Vec2f{90.0f, 30.0f}, button_decrease)
                .end()
            .end()
        .end()
    .end()
    .complete_menu();

    menu.submit(ui_renderer);

    while (!event_manager.is_quitting()) {

        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        float camera_vel = 2.0f;
        float camera_angle = 0.01f;
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_W)) {
            camera.move_local({0.0f, 0.0f, -camera_vel});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_S)) {
            camera.move_local({0.0f, 0.0f, camera_vel});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_A)) {
            camera.move_local({-camera_vel, 0.0f, 0.0f});
        }
        if (event_manager.keyboard().key_press(AMB::KeyCode::KEY_CODE_D)) {
            camera.move_local({camera_vel, 0.0f, 0.0f});
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
        mat::Mat4f m = mat::dot(mat::graph::translate3<float>(cube_position), mat::dot(mat::graph::rotateY<float>(angle_a), mat::graph::rotateX<float>(angle_b)));
 
        // Draw 3D
        shader.use_shader();
        shader.set_mat4f("u_mvp", mat::dot(vp, m));
        renderer.draw_arrays(vao, shader);

        // Draw UI
        renderer.set_depth_test(false);
        renderer.set_blend(true);
        renderer.set_cull_face(false);

        //glDepthMask(GL_FALSE);

        menu.update(event_manager);
        ui_renderer.build_mesh();
        ui_renderer.draw();

        //glDepthMask(GL_TRUE);

        // Restore state
        renderer.set_depth_test(true);
        renderer.set_blend(true);
        renderer.set_cull_face(true);

        // Present the frame
        window.present();

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}