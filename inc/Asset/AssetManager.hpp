#pragma once

#include "Asset/AssetStorage.hpp"

#include "Audio/Audio.hpp"
#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"
#include "Graphic/Shader.hpp"

namespace AMB {

struct AssetManager {
    AssetStorage<Music> musics;
    AssetStorage<Sound> sounds;
    AssetStorage<Shader> shaders;
};

}