#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Logger/Logger.hpp"

namespace AMB {

class FontSystem {
public:
    FontSystem();

    ~FontSystem();

    FT_Library& get_library();

private:
    FT_Library m_ft_lib;
};

}