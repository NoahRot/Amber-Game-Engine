#include "Window/Window.hpp"

int main(int argc, char* argv[]) {
    
    ora::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    window.present();

    SDL_Delay(1000);
    
    return 0;
}