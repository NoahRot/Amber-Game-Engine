#pragma once

#include "inttypes.h"
#include <cmath>

namespace mat {

inline float fade_function_3(float t){
    return 3*t*t - 2*t*t*t;
}

inline float fade_function_5(float t){
    return 6*t*t*t*t*t - 15*t*t*t*t + 10*t*t*t;
}

template<typename T>
inline T linear_interpolation(T a, T b, float t) {
    return a * t + b * (1.0f - t);
}

template<typename T>
inline T inverse_linear_interpolation(T a, T b, T v) {
    return  (v - a) / (b - a);
}

template<typename T>
inline T cubic_interpolation(T a, T b, float t) {
    float fade(fade_function_3(t));
    return (1.0f-fade)*a + fade*b;
}

template<typename T>
inline T quintic_interpolation(T a, T b, float t) {
    float fade(fade_function_5(t));
    return (1.0f-fade)*a + fade*b;
}

inline float sigmoid(float x) {
    return 2/(1 + expf(-x)) - 1;
}

}