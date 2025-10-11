#include "Window/Window.hpp"
#include "Time/Timer.hpp"
#include "Event/Event.hpp"
#include "Audio/Audio.hpp"
#include "Audio/Music.hpp"
#include "Asset/AssetManager.hpp"
#include "Asset/AssetFactory.hpp"

int main(int argc, char* argv[]) {

    AMB::Window window(800, 600, "Test Window", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);
    AMB::EventManager event_manager(&window);
    AMB::Timer timer(60);
    AMB::Audio audio(MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MID|MIX_INIT_OPUS, 22050, 0x8010, 2, 1024);
    AMB::AssetManager asset_manager;
    AMB::FontSystem font_system;
    AMB::AssetFactory asset_factory(asset_manager, font_system);

    AMB::AssetHandle music_handle = asset_factory.create_music(std::string("test/res/Sky Corsair.mp3"));
    if (!asset_manager.musics.validity(music_handle)) {
        std::cerr << "Failed to add music asset." << std::endl;
        return EXIT_FAILURE;
    }
    AMB::AssetHandle sound_handle = asset_factory.create_sound(std::string("test/res/but.wav"));
    if (!asset_manager.sounds.validity(sound_handle)) {
        std::cerr << "Failed to add sound asset." << std::endl;
        return EXIT_FAILURE;
    }

    AMB::Music& music = asset_manager.musics.get(music_handle);
    AMB::Sound& sound = asset_manager.sounds.get(sound_handle);

    while (!event_manager.is_quitting()) {
        event_manager.manage();

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_SPACE)) {
            if (!music.is_playing()) {
                music.play();
            } else if (music.is_paused()) {
                music.resume();
            } else {
                music.pause();
            }
        }

        if (event_manager.keyboard().key_down(AMB::KeyCode::KEY_CODE_RETURN)) {
            sound.play();
        }

        window.present(); 

        timer.wait();

    }

    return 0;
}