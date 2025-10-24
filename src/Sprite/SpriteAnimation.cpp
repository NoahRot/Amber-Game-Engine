#include "Sprite/SpriteAnimation.hpp"

namespace AMB {

SpriteAnimation::SpriteAnimation(SpriteSheet& sprite_sheet, uint32_t begin_sprite, uint32_t end_sprite, uint32_t frame_time)
: m_sprite_sheet(sprite_sheet), m_begin_sprite(begin_sprite), m_end_sprite(end_sprite), m_current_sprite(begin_sprite),
    m_frame_time(frame_time), m_current_time(0)
{}

void SpriteAnimation::update(uint32_t dt) {
    m_current_time += dt;
    while(m_current_time > m_frame_time) {
        ++m_current_sprite;
        if (m_current_sprite > m_end_sprite) {
            m_current_sprite = m_begin_sprite;
        }
        m_current_time -= m_frame_time;
    }
}

Sprite SpriteAnimation::get_current_sprite() {
    return m_sprite_sheet.get_sprite(m_current_sprite);
}

}