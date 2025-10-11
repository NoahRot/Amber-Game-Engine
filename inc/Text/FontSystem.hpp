#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Logger/Logger.hpp"

namespace AMB {

class FontSystem {
public:
    FontSystem() {
        if (FT_Init_FreeType(&m_ft_lib) != 0) {
            Logger::instance().log(Fatal, "Can not initialize FreeType");
            exit(EXIT_FAILURE);
        }
    }

    ~FontSystem() {
        FT_Done_FreeType(m_ft_lib);
    }

    FT_Library& get_library() {
        return m_ft_lib;
    }

private:
    FT_Library m_ft_lib;
};

}