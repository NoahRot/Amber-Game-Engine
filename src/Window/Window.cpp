#include "Window/Window.hpp"

namespace AMB {

Window::Window(uint32_t width, uint32_t height, std::string title, uint32_t sdl_flags, uint32_t win_flags) 
: m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
    // Init SDL
    if (SDL_Init(sdl_flags) != 0) {
        std::string sdl_error(SDL_GetError());
        SDL_Quit();
        Logger::instance().log(Info, "Can not initialize SDL. SDL ERROR : " + sdl_error);
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "SDL initialize");

    // Set Attribute for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Disable old functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true); // Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create SDL window
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, win_flags);
    if (!m_window) {
        std::string sdl_error(SDL_GetError());
        Logger::instance().log(Info, "Can not create SDL window. SDL ERROR : " + sdl_error);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "SDL Window created");

    // Create the opengl context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        std::string sdl_error(SDL_GetError());
        Logger::instance().log(Info, "Can not create OpenGL context. SDL ERROR : " + sdl_error);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "OpenGL context created");

    // Init GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        Logger::instance().log(Info, "Can not init GLAD");
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    Logger::instance().log(Info, "GLAD initialize");

    // Tell OpenGL where the left bottom corner is and what the dimensions of the windows are
    glViewport(0, 0, m_width, m_height);
    Logger::instance().log(Info, "Viewport set");

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Logger::instance().log(Info, "Window created");
}

Window::~Window() {
    // Destroy OpenGl context
    if(m_context) {
        SDL_GL_DeleteContext(m_context);
    }
    
    // Destroy window
    if(m_window) {
        SDL_DestroyWindow(m_window);
    }

    // Quit SDL
    SDL_Quit();

    Logger::instance().log(Info, "Window destroyed");
}

uint32_t Window::get_width() const {
    return m_width;
}

uint32_t Window::get_height() const {
    return m_height;
}

void Window::present() const {
    SDL_GL_SwapWindow(m_window);
}

}