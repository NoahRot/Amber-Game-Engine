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

    bool serialize_txt(const Hierarchy& hierarchy, std::string path);

    bool deserialize_txt(Hierarchy& hierarchy, std::string path);

private:
    void write_bin(const Group& group, std::ofstream& file);

    void read_bin(Group& group, std::ifstream& file);

    void write_txt(const Group& group, std::ofstream& file, int indent = 0);

    void read_txt(Group& group, std::ifstream& file, int level = 0) {
        std::string line;
        while (std::getline(file, line)) {

            // Find the current line's indentation level
            size_t current_indent = 0; 
            while (current_indent < line.size() && line[current_indent] == ' ') {
                ++current_indent;
            }
            int current_level = current_indent / 2;

            std::cout << line << std::endl;
            std::cout << "READLINE" << std::endl;

            if (current_level == level + 1) {
                // This line is a subgroup or data of the current group
                std::string content = line.substr(current_indent);
                if (content.size() >= size_t(5) && content.substr(0,5) == "Group") {
                    // It's a subgroup
                    std::string group_name = content.substr(6); // Remove "Group " and ":"
                    Group& subgroup = group[group_name];
                    std::cout << "Reading subgroup: " << group_name << std::endl;
                    //read_txt(subgroup, file, current_level);

                } else if (content.size() >= 4 && content.substr(0,4) == "Data") {
                    // It's a data entry
                    std::string data_content = content.substr(5, content.size() - 6); // Remove "Data " and ":"

                    // Find the name
                    size_t colon_pos = data_content.find(' ');
                    std::string data_name = data_content.substr(0, colon_pos);
                    data_content = data_content.substr(colon_pos + 1);

                    // Find the type 
                    data_content = data_content.substr(5); // Remove "Type:"
                    colon_pos = data_content.find(' ');
                    std::string type_str = data_content.substr(0, colon_pos);
                    DataType data_type = static_cast<DataType>(std::stoi(type_str));
                    data_content = data_content.substr(colon_pos + 1);

                    // Find the size
                    data_content = data_content.substr(5); // Remove "Size:"
                    colon_pos = data_content.find(' ');
                    std::string size_str = data_content.substr(0, colon_pos);
                    size_t data_size = static_cast<size_t>(std::stoul(size_str));
                    data_content = data_content.substr(colon_pos + 1);

                    std::cout << "Reading data: " << data_name << " Type: " << static_cast<int>(data_type) << " Size: " << data_size << std::endl;
                }
            }

            read_txt(group, file, level);
        }
    }

    const char BINARY_FILE_HEADER[4] = {'A', 'M', 'B', 'R'};
    const char EXTENSION_BIN[7] = ".amber";
    const char EXTENSION_TXT[11] = ".amber_txt";
};

}