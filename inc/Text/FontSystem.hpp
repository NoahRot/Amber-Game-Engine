#pragma once

#include "Logger/Logger.hpp"

struct FT_LibraryRec_;   // forward declaration FreeType
typedef struct FT_LibraryRec_* FT_Library;

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