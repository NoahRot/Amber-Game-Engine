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
#include "Text/Text.hpp"

#include <thread>
#include <algorithm>
#include <map>

typedef double T;
typedef mat::Complex<T> complex;

struct Vertex {
    float x, y;  // Position
    float u, v;  // Texture coordinates
};

enum class FractalMode { 
    MANDELBROT,
    JULIA
};

std::string to_string(complex c) {
    return "(" + std::to_string(c.real()) + ", " + std::to_string(c.imag()) + "i)";
}

/*
============================================
===== Mandelbrot computation functions =====
============================================
*/

uint32_t mandelbrot_serie(complex c, uint32_t max_iter) {
    uint32_t iter = 0;
    complex z(0.0, 0.0);

    while (z.modulus2() <= 4.0 && iter < max_iter) {
        z = z * z + c;
        ++iter;
    }

    return iter;
}

void mandelbrot_set(complex upper_left, complex lower_right, uint32_t width, uint32_t height, uint32_t max_iter,
    std::vector<uint32_t>& convergence) {
    
    T dr = (lower_right.real() - upper_left.real())/width;
    T di = (lower_right.imag() - upper_left.imag())/height;

    for (uint32_t j(0) ; j < height ; ++j) {
        for (uint32_t i(0) ; i < width ; ++i) {
            convergence[i + j*width] = mandelbrot_serie(upper_left + complex(dr*i, di*j), max_iter);
        }
    }
}

void mandelbrot_worker(complex upper_left, complex lower_right, uint32_t width, uint32_t height,
    uint32_t y_start, uint32_t y_end, uint32_t max_iter, std::vector<uint32_t>& convergence)
{
    T dr = (lower_right.real() - upper_left.real()) / width;
    T di = (upper_left.imag() - lower_right.imag()) / height;

    for (uint32_t j = y_start; j < y_end; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            complex c(
                upper_left.real() + i * dr,
                upper_left.imag() - j * di
            );

            convergence[i + j * width] = mandelbrot_serie(c, max_iter);
        }
    }
}

void mandelbrot_multi_core(complex upper_left, complex lower_right, uint32_t width, uint32_t height, uint32_t max_iter,
    std::vector<uint32_t>& convergence)
{
    uint32_t num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 2) {
        num_threads = 1;
    } else {
        num_threads -= 2;
    }

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    uint32_t rows_per_thread = height / num_threads;

    for (uint32_t t = 0; t < num_threads; ++t) {
        uint32_t y_start = t * rows_per_thread;
        uint32_t y_end   = (t == num_threads - 1) ? height : y_start + rows_per_thread;

        threads.emplace_back(
            mandelbrot_worker,
            upper_left,
            lower_right,
            width,
            height,
            y_start,
            y_end,
            max_iter,
            std::ref(convergence)
        );
    }

    for (auto& th : threads)
        th.join();
}

/*
=======================================
===== Julia computation functions =====
=======================================
*/

uint32_t julia_serie(complex z, complex c, uint32_t max_iter) {
    uint32_t iter = 0;

    while (z.modulus2() <= 4.0 && iter < max_iter) {
        z = z * z + c;
        ++iter;
    }

    return iter;
}

void julia_set(complex c, complex upper_left, complex lower_right, uint32_t width, uint32_t height, uint32_t max_iter,
    std::vector<uint32_t>& convergence) {
    
    T dr = (lower_right.real() - upper_left.real())/width;
    T di = (lower_right.imag() - upper_left.imag())/height;

    for (uint32_t j(0) ; j < height ; ++j) {
        for (uint32_t i(0) ; i < width ; ++i) {
            convergence[i + j*width] = julia_serie(upper_left + complex(dr*i, di*j), c, max_iter);
        }
    }
}

void julia_worker(complex julia_c, complex upper_left, complex lower_right, uint32_t width, uint32_t height,
    uint32_t y_start, uint32_t y_end, uint32_t max_iter, std::vector<uint32_t>& convergence)
{
    T dr = (lower_right.real() - upper_left.real()) / width;
    T di = (upper_left.imag() - lower_right.imag()) / height;

    for (uint32_t j = y_start; j < y_end; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            complex z(
                upper_left.real() + i * dr,
                upper_left.imag() - j * di
            );

            convergence[i + j * width] = julia_serie(z, julia_c, max_iter);
        }
    }
}

void julia_multi_core(complex julia_c, complex upper_left, complex lower_right, uint32_t width, uint32_t height, uint32_t max_iter,
    std::vector<uint32_t>& convergence)
{
    uint32_t num_threads = std::thread::hardware_concurrency();
    if (num_threads <= 2) {
        num_threads = 1;
    } else {
        num_threads -= 2;
    }

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    uint32_t rows_per_thread = height / num_threads;

    for (uint32_t t = 0; t < num_threads; ++t) {
        uint32_t y_start = t * rows_per_thread;
        uint32_t y_end   = (t == num_threads - 1) ? height : y_start + rows_per_thread;

        threads.emplace_back(
            julia_worker,
            julia_c,
            upper_left,
            lower_right,
            width,
            height,
            y_start,
            y_end,
            max_iter,
            std::ref(convergence)
        );
    }

    for (auto& th : threads)
        th.join();
}

/*
=========================
===== Fractal class =====
=========================
*/

class Fractal {
public:
    Fractal(complex up_left, complex low_right, uint32_t width, uint32_t height, uint32_t max_iter)
    : m_up_left(up_left), m_low_right(low_right), m_width(width), m_height(height), 
        m_max_iter(max_iter), m_convergence(m_width*m_height, 0), m_mode(FractalMode::MANDELBROT), m_julia_c(0.0, 0.0)
    {
        AMB::Logger::instance().log(AMB::Info, "Number of CPU threads :" + std::to_string(std::thread::hardware_concurrency()));

        recompute();
    }

    std::vector<uint32_t>& get_convergence() { return m_convergence; }

    void mandelbrot() {
        mandelbrot_multi_core(m_up_left, m_low_right, m_width, m_height, m_max_iter, m_convergence);
    }

    void julia() {
        julia_multi_core(m_julia_c, m_up_left, m_low_right, m_width, m_height, m_max_iter, m_convergence);
    }

    void recompute() {
        switch (m_mode)
        {
        case FractalMode::MANDELBROT:
            mandelbrot();
            break;

        case FractalMode::JULIA:
            julia();
            break;
        
        default:
            break;
        }
    }

    void set_mode(FractalMode mode) {
        if (mode != m_mode) {
            m_mode = mode;
            recompute();
            clean_undo();
        }
    }

    FractalMode get_mode() {
        return m_mode;
    }

    complex complex_at_pixel(mat::Vec2i position) const {
        // Pixel size in complex plane
        T dx = (m_low_right.real() - m_up_left.real()) / T(m_width);
        T dy = (m_up_left.imag() - m_low_right.imag()) / T(m_height);

        // Map pixel (x, y) to complex number
        T real_part = m_up_left.real() + position[0] * dx;
        T imag_part = m_low_right.imag() + position[1] * dy; // <-- bottom-left origin

        return complex(real_part, imag_part);
    }

    void set_new_position(complex up_left, complex low_right) {
        m_undo_storage.push({m_up_left, m_low_right});
        m_up_left = up_left;
        m_low_right = low_right;

        recompute();
    }

    void undo() {
        if (!m_undo_storage.empty()) {
            m_up_left = m_undo_storage.top().first;
            m_low_right = m_undo_storage.top().second;
            m_undo_storage.pop();

            recompute();
        }
    }

    void clean_undo() {
        while (!m_undo_storage.empty()) {
            m_undo_storage.pop();
        }
    }

    void set_max_iteration(uint32_t max_iter) {
        m_max_iter = max_iter;
        recompute();
    }

    uint32_t get_max_iteration() {
        return m_max_iter;
    }

    void set_julia_c(complex julia_c) {
        m_julia_c = julia_c;
        if (m_mode == FractalMode::JULIA) {
            recompute();
        }
    }

    complex get_julia_c() const {
        return m_julia_c;
    }

private:
    complex m_up_left, m_low_right;
    uint32_t m_width, m_height;
    uint32_t m_max_iter;
    std::vector<uint32_t> m_convergence;
    std::stack<std::pair<complex, complex>> m_undo_storage;
    FractalMode m_mode;
    complex m_julia_c;
};

std::map<int, std::string> COLOR_MAP_SELECTION {
    {0, "White"},
    {1, "Vidris"},
    {2, "Fire"},
    {3, "Ocean"},
    {4, "Inferno"},
    {5, "Plasma"},
    {6, "Magma"},
    {7, "Cividis"},
    {8, "Palette"},
    {9, "Modulo"},
    {10, "Modulo RGB"}
};

void build_text(AMB::TextRenderer& text_renderer, uint32_t max_iter, FractalMode mode, uint32_t height, 
                complex julia_c, complex mouse_pos, int color_selection) {
    std::string text;

    switch (mode)
    {
    case FractalMode::MANDELBROT:
        text = "Set: Mandelbrot\n";
        break;

    case FractalMode::JULIA:
        text = "Set: Julia\nConstant: " + to_string(julia_c) + "\n";
        break;
    
    default:
        break;
    }

    text += "Max iteration: " + std::to_string(max_iter) + "\n";
    text += "Mouse position: " + to_string(mouse_pos) + "\n";
    text += "Color selection: " + COLOR_MAP_SELECTION[color_selection] + "\n";

    AMB::Font& font = text_renderer.get_font();
    text_renderer.reset();
    text_renderer.submit_text(text, mat::Vec3f{0.0f,(float)height - (float)font.get_height(),+0.5f}, 1.0f, 1.0f, 1.0f, 1.0f);
    text_renderer.build_mesh();
}

void reset_fractal(Fractal& fractal, float win_ratio, FractalMode mode = FractalMode::MANDELBROT) {
    complex upper_left(-1.0/2.0 * win_ratio*4.0,  2.0);
    complex lower_right(1.0/2.0 * win_ratio*4.0, -2.0);
    uint32_t max_iter = 1000;

    fractal.set_max_iteration(1);

    fractal.set_new_position(upper_left, lower_right);
    fractal.set_mode(mode);
    fractal.set_max_iteration(max_iter);
}

/*
=========================
===== Main function =====
=========================
*/

int main(int argc, char* argv[]) {

    AMB::Window window(1920, 1080, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::AssetManager asset_manager;
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);
    AMB::Renderer renderer;

    AMB::Logger& logger = AMB::Logger::instance();

    uint32_t width = window.get_width();
    uint32_t height = window.get_height();
    T win_ratio = (float)width/(float)height;
    complex upper_left(-1.0/2.0 * win_ratio*4.0,  2.0);
    complex lower_right(1.0/2.0 * win_ratio*4.0, -2.0);
    uint32_t max_iter = 1000;
    int color_selection = 0;

    Fractal fractal(upper_left, lower_right, width, height, max_iter);
    std::vector<uint32_t> convergence(height*height, 0);

    /*
    =======================
    ===== Load assets =====
    =======================
    */

    AMB::AssetHandle shader_fractal_handle = asset_factory.create_shader(std::string("test/res/Mandelbrot.vert"), std::string("test/res/Mandelbrot.frag"));
    if (!asset_manager.shaders.validity(shader_fractal_handle)) {
        logger.log(AMB::Fatal, "Fail to load fractal shader");
        return EXIT_FAILURE; 
    }

    AMB::AssetHandle shader_text_handle = asset_factory.create_shader(std::string("test/res/Text.vert"), std::string("test/res/Text.frag"));
    if (!asset_manager.shaders.validity(shader_text_handle)) {
        logger.log(AMB::Fatal, "Fail to load text shader");
        return EXIT_FAILURE; 
    }
    AMB::Shader& shader_text = asset_manager.shaders.get(shader_text_handle);

    AMB::AssetHandle font_handle = asset_factory.create_font("test/res/OpenSans.ttf", 24);
    if (!asset_manager.fonts.validity(font_handle)) {
        logger.log(AMB::Fatal, "Fail to load font");
        return EXIT_FAILURE; 
    }
    AMB::Font& font = asset_manager.fonts.get(font_handle);

    AMB::AssetHandle texture_fractal_handle = asset_factory.create_texture_from_data(
        width, height, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
    if (!asset_manager.textures.validity(texture_fractal_handle)) {
        logger.log(AMB::Fatal, "Fail to load fractal texture");
        return EXIT_FAILURE;
    }

    /*
    =====================================
    ===== Create background texture =====
    =====================================
    */

    std::vector<Vertex> vertices = { 
        Vertex{0.0f,            0.0f,               0.0f, 0.0f}, // Bottom left vertex (Red)
        Vertex{0.0f,            (float)height,      0.0f, 1.0f}, // Bottom right vertex (Green)
        Vertex{(float)width,    (float)height,      1.0f, 1.0f}, // Top right vertex (Blue)
        Vertex{(float)width,    0.0f,               1.0f, 0.0f}  // Top left vertex (White)
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    AMB::VertexAttribLayout layout;
    layout.add_float(2, false); // Position attribute (2 floats)
    layout.add_float(2, false); // Texture coordinate attribute (2 floats)

    std::shared_ptr<AMB::VertexArray> vao_ptr = AMB::create_vertex_array();
    std::shared_ptr<AMB::VertexBuffer> vbo_ptr = AMB::create_vertex_buffer(vertices, true);
    std::shared_ptr<AMB::IndexBuffer> ibo_ptr = AMB::create_index_buffer(indices, true);
    vao_ptr->add_vertex_buffer(vbo_ptr, layout);
    vao_ptr->set_index_buffer(ibo_ptr);

    AMB::Shader& shader_fractal = asset_manager.shaders.get(shader_fractal_handle);
    AMB::Texture& texture_fractal = asset_manager.textures.get(texture_fractal_handle);
    texture_fractal.set_filter(AMB::TextureFilter::LINEAR, AMB::TextureFilter::LINEAR);

    mat::Vec2i mouse_pos0;
    mat::Vec2i mouse_pos1;
    bool mouse_hold = false;

    AMB::TextRenderer text_renderer(font, shader_text, 2048);

    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, width, 0.0f, height, -1.0f, 1.0f);

    renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    texture_fractal.bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        int mouse_x, mouse_y;
        event_manager.mouse().mouse_position(mouse_x, mouse_y);
        mouse_pos1 = mat::Vec2i{mouse_x, mouse_y};
        complex mouse_c1 = fractal.complex_at_pixel({mouse_pos1[0], (int)height - mouse_pos1[1]});

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_UP)) {
            int mi = fractal.get_max_iteration() + 500;
            fractal.set_max_iteration(mi);
            fractal.recompute();
            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }
        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_DOWN)) {
            int mi = fractal.get_max_iteration();
            mi - 500 < 10 ? mi = 10 : mi -= 500;
            fractal.set_max_iteration(mi);
            fractal.recompute();
            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_RIGHT)) {
            color_selection += 1;
            if (color_selection > 10) {
                color_selection = 10;
            }
        }
        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_LEFT)) {
            color_selection -= 1;
            if (color_selection < 0) {
                color_selection = 0;
            }
        }

        if (event_manager.mouse().button_down(AMB::MouseButton::MOUSE_LEFT)) {
            mouse_pos0 = mat::Vec2i{mouse_x, mouse_y};
            mouse_hold = true;
        }

        if (event_manager.mouse().button_down(AMB::MouseButton::MOUSE_EXTRA_1) or 
            event_manager.keyboard().key_down(AMB::KEY_CODE_DELETE)) {
            fractal.undo();
            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }

        if (event_manager.mouse().button_up(AMB::MouseButton::MOUSE_LEFT)) {
            mouse_hold = false;
            complex c0 = fractal.complex_at_pixel({mouse_pos0[0], (int)height - mouse_pos0[1]});

            T x_length = abs(c0[0] - mouse_c1[0]);
            T y_length = x_length/win_ratio;

            complex new_up_left(c0[0] - x_length, c0[1] + y_length);
            complex new_down_right(c0[0] + x_length, c0[1] - y_length);
            fractal.set_new_position(new_up_left, new_down_right);

            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }

        if (event_manager.keyboard().key_down(AMB::KEY_CODE_M)) {
            reset_fractal(fractal, win_ratio, FractalMode::MANDELBROT);
            fractal.set_mode(FractalMode::MANDELBROT);

            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }

        if (event_manager.keyboard().key_down(AMB::KEY_CODE_J)) {
            int x,y;
            event_manager.mouse().mouse_position(x, y);
            complex c0 = fractal.complex_at_pixel({x, (int)height - y});
            
            reset_fractal(fractal, win_ratio, FractalMode::MANDELBROT);
            fractal.set_mode(FractalMode::JULIA);

            fractal.set_julia_c(c0);
            texture_fractal.bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, fractal.get_convergence().data());
        }

        // Create the text
        build_text(text_renderer, fractal.get_max_iteration(), fractal.get_mode(), height, fractal.get_julia_c(), 
            mouse_c1, color_selection);
        
        // Clear the screen
        renderer.clear();

        // Draw the fractal
        texture_fractal.bind(0);
        shader_fractal.use_shader();
        shader_fractal.set_1f("u_max_iter", (float)fractal.get_max_iteration());
        shader_fractal.set_mat4f("u_mvp", mvp);
        shader_fractal.set_1i("u_mouse_quad", mouse_hold);
        shader_fractal.set_2i("u_mouse_pos0", mouse_pos0);
        shader_fractal.set_2i("u_mouse_pos1", mouse_pos1);
        shader_fractal.set_1f("u_win_ratio", win_ratio);
        shader_fractal.set_1i("u_color_selection", color_selection);
        renderer.draw_arrays(vao_ptr, shader_fractal);

        // Draw text
        text_renderer.draw(mvp);

        // Present the frame
        window.present(); 

        // Wait to maintain the target frame rate
        timer.wait();

    }

    return 0;
}