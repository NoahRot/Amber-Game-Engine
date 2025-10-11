#pragma once

#include <inttypes.h>

namespace AMB {

struct Character {
    float u, v, w, h;       // Position and dimension on the texture atlas
    int32_t width, height;  // Width and height in pixel
    int32_t bearing_x, bearing_y;
    int64_t advance;        // Advance to the next char
};

}