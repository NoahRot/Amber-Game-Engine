#include "Window/Window.hpp"
#include "Time/Timer.hpp"
#include "Event/Event.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        window.present();

        timer.wait();

    }

    return 0;
}