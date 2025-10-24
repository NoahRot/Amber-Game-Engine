#pragma once

#include <random>

namespace AMB {

class Lehmer32 {
public:
    Lehmer32(uint32_t seed);

    void set_seed(uint32_t s);

    uint32_t get_seed() const;

    uint32_t next_uint32();

    float next_float32();

    uint32_t uniform_uint32(uint32_t min, uint32_t max);

    int32_t uniform_int32(int32_t min, int32_t max);

    float uniform_float(float min, float max);

    float gaussian(float mean = 0.0f, float stddev = 1.0f);

private:
    uint32_t m_state;
    uint32_t m_seed;
};

}