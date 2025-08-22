#pragma once

#include "Asset/AssetStorage.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

namespace AMB {

struct AssetManager {
    AssetStorage<Music> musics;
    AssetStorage<Sound> sounds;
};

}