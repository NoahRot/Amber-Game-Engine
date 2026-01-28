#include <ft2build.h>
#include FT_FREETYPE_H

#include "Text/FontSystem.hpp"

namespace AMB {

FontSystem::FontSystem() {
    if (FT_Init_FreeType(&m_ft_lib) != 0) {
        Logger::instance().log(Fatal, "Can not initialize FreeType");
        exit(EXIT_FAILURE);
    }
}

FontSystem::~FontSystem() {
    FT_Done_FreeType(m_ft_lib);
}

FT_Library& FontSystem::get_library() {
    return m_ft_lib;
}

}