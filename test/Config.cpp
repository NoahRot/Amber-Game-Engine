#include "Configuration/Configuration.hpp"

int main(int argc, char* argv[]) {

    AMB::Configuration& config = AMB::Configuration::instance();
    config.set_win_title("Changed Title");
    config.set_win_height(720);
    config.set_win_width(1280);

    config.initialize();
    config.save_configuration("test/config");

    config.load_configuration("test/config");

    AMB::Hierarchy config_hierarchy = config.config_to_hierarchy();

    AMB::print_hierarchy(config_hierarchy);
    std::string title = config.get_win_title();
    std::cout << "Window title: " << title << std::endl;
    uint32_t width = config.get_win_width();
    std::cout << "Window width: " << width << std::endl;
    uint32_t height = config.get_win_height();
    std::cout << "Window height: " << height << std::endl;

    return 0; 
}