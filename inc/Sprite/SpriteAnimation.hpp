#pragma once

#include "Sprite/SpriteSheet.hpp"

namespace AMB {

class SpriteAnimation {
public:
    SpriteAnimation(SpriteSheet& sprite_sheet, uint32_t begin_sprite, uint32_t end_sprite, uint32_t frame_time);

    void update(uint32_t dt);

    Sprite get_current_sprite();

private:
    SpriteSheet& m_sprite_sheet;
    uint32_t m_begin_sprite, m_end_sprite, m_current_sprite;
    uint32_t m_frame_time, m_current_time;
};

}