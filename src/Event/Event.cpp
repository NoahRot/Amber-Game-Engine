#include "Event/Event.hpp"

namespace AMB {

EventManager::EventManager(Window* window)
: m_quit(false)
{
    Logger::instance().log(Info, "Event created");

    m_mouse.set_window_height(window->get_height());
}

EventManager::~EventManager() {
    Logger::instance().log(Info, "Event destroyed");
}

void EventManager::manage() {

    // Reset events
    m_keyboard.manage();
    m_mouse.manage();

    // Poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_quit = true;
                break;

            case SDL_KEYDOWN:
                m_keyboard.manage_down((KeyCode)event.key.keysym.scancode);
                break;

            case SDL_KEYUP:
                m_keyboard.manage_up((KeyCode)event.key.keysym.scancode);
                break;

            case SDL_MOUSEBUTTONDOWN:
                m_mouse.manage_down(event.button.button - 1);
                break;

            case SDL_MOUSEBUTTONUP:
                m_mouse.manage_up(event.button.button - 1);
                break;
        }
    }
}

void EventManager::reset() {
    m_keyboard.reset();
    m_quit = false;
}

bool EventManager::is_quitting() const {
    return m_quit;
}

void EventManager::quit() {
    m_quit = true;
}

const Keyboard& EventManager::keyboard() const {
    return m_keyboard;
}

const Mouse& EventManager::mouse() const {
    return m_mouse;
}

}