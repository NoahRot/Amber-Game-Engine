#pragma once

#include "Asset/AssetStorage.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"
#include "Text/Font.hpp"

namespace AMB {

struct AssetManager {
    AssetStorage<Music> musics;
    AssetStorage<Sound> sounds;
    AssetStorage<Shader> shaders;
    AssetStorage<Texture> textures;
    AssetStorage<Font> fonts;
};

}