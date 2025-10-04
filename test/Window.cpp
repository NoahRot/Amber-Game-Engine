#include "Window/Window.hpp"

int main(int argc, char* argv[]) {
    
    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    window.present();

    SDL_Delay(1000);

    AMB::Logger& logger = AMB::Logger::instance();
    logger.log(AMB::LogLevel::Info, "This is an info message.");
    logger.log(AMB::LogLevel::Warning, "This is a warning message.");
    logger.log(AMB::LogLevel::Error, "This is an error message.");
    logger.log(AMB::LogLevel::Debug, "This is a debug message.");
    logger.log(AMB::LogLevel::Fatal, "This is a fatal message.");
    
    return 0;
}