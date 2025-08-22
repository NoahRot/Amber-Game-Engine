#pragma once

#include <typeinfo>
#include <typeindex>
#include <inttypes.h>

namespace AMB {

struct AssetHandle {
    int32_t index;
    std::type_index type;
};

}