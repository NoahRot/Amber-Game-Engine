#pragma once

#include <string>
#include <inttypes.h>
#include <iostream>
#include <fstream>

#include "Serialization/Hierarchy.hpp"

namespace AMB {

class Serializer {
public:
    bool serialize_bin(const Hierarchy& hierarchy, std::string path);

    bool deserialize_bin(Hierarchy& hierarchy, std::string path);

private:
    void write_bin(const Group& group, std::ofstream& file);

    void read_bin(Group& group, std::ifstream& file);

    const char BINARY_FILE_HEADER[4] = {'A', 'M', 'B', 'R'};
    const char EXTENSION_BIN[7] = ".amber";
};

}