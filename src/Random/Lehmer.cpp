#include "Random/Lehmer.hpp"

namespace AMB {

Lehmer32::Lehmer32(uint32_t seed) 
: m_state(seed ? seed : 0x12345678u), m_seed(m_state)
{}

void Lehmer32::set_seed(uint32_t s) {
    m_state = s ? s : 0x12345678u;
    m_seed = m_state;
}

uint32_t Lehmer32::get_seed() const { 
    return m_seed; 
}

uint32_t Lehmer32::next_uint32() {
    //m_state  += 0xe120fc25;
    m_state  += 0xe120fc15u;
    uint64_t mix;
    mix = (uint64_t)m_state  * 0x4a39b70d;
    uint32_t m1 = (mix >> 32) ^ mix;
    mix = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (mix >> 32) ^ mix;
    return m2;
}

float Lehmer32::next_float32() {
    constexpr float invMax = 1.0f / static_cast<float>(UINT32_MAX);
    return next_uint32() * invMax;
}

uint32_t Lehmer32::uniform_uint32(uint32_t min, uint32_t max) {
    if (min > max) std::swap(min, max);
    uint32_t range = max - min + 1;
    return min + next_uint32() % range;
}

int32_t Lehmer32::uniform_int32(int32_t min, int32_t max) {
    if (min > max) std::swap(min, max);
    // Convert to unsigned range to avoid overflow when subtracting negatives
    uint32_t range = static_cast<uint32_t>(static_cast<uint64_t>(max) - static_cast<int64_t>(min) + 1);
    return min + static_cast<int32_t>(next_uint32() % range);
}

float Lehmer32::uniform_float(float min, float max) {
    if (min > max) std::swap(min, max);
    return min + (max - min) * next_float32();
}

float Lehmer32::gaussian(float mean, float stddev) {
    float u1 = next_float32();
    float u2 = next_float32();
    if (u1 < 1e-7f) u1 = 1e-7f;
    float z0 = std::sqrt(-2.0f * std::log(u1)) * std::cos(6.28318530718f * u2);
    return mean + z0 * stddev;
}

}