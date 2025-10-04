#include "Serialization/Serializer.hpp"

namespace AMB {

bool Serializer::serialize_bin(const Hierarchy& hierarchy, std::string path) {
    std::ofstream file(path + EXTENSION_BIN, std::ios::binary);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Failed to open file for binary serialization: " + path);
        return false;
    }

    // Write header
    file.write(BINARY_FILE_HEADER, sizeof(BINARY_FILE_HEADER));

    // Write the name of the hierarchy
    uint8_t name_length = hierarchy.name.size();
    file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
    file.write(hierarchy.name.c_str(), name_length);

    write_bin(hierarchy.root, file);

    file.close();
    return true;
}

void Serializer::write_bin(const Group& group, std::ofstream& file) {

    // Get number of data and subgroups
    uint16_t num_data = group.data.size();
    uint16_t num_subgroups = group.subgroups.size(); 
    
    // Write data
    file.write(reinterpret_cast<const char*>(&num_data), sizeof(num_data));
    for (const auto& [name, data] : group.data) {
        // Meta data
        uint8_t name_length = name.size();
        file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        file.write(name.c_str(), name_length);
        file.write(reinterpret_cast<const char*>(&data.type), sizeof(data.type));

        // Actual data
        uint32_t data_size = data.data.size();
        file.write(reinterpret_cast<const char*>(&data_size), sizeof(data_size));
        file.write(reinterpret_cast<const char*>(data.data.data()), data_size);
    }

    // Write subgroups
    file.write(reinterpret_cast<const char*>(&num_subgroups), sizeof(num_subgroups));
    for (const auto& [name, subgroup] : group.subgroups) {
        // Meta data
        uint8_t name_length = name.size();
        file.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        file.write(name.c_str(), name_length);

        // Recursive call
        write_bin(subgroup, file);
    }
}

bool Serializer::deserialize_bin(Hierarchy& hierarchy, std::string path) {
    std::ifstream file(path + EXTENSION_BIN, std::ios::binary);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Failed to open file for binary deserialization: " + path);
        return false;
    }

    // Read and verify header
    char header[4];
    file.read(header, sizeof(header));
    if (header[0] != BINARY_FILE_HEADER[0] || header[1] != BINARY_FILE_HEADER[1] ||
        header[2] != BINARY_FILE_HEADER[2] || header[3] != BINARY_FILE_HEADER[3]) {
        Logger::instance().log(Error, "Invalid file format for binary deserialization: " + path);

        file.close();
        return false;
    }

    // Read the name of the hierarchy
    uint8_t name_length;
    file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
    hierarchy.name.resize(name_length);
    file.read(&hierarchy.name[0], name_length);

    read_bin(hierarchy.root, file);

    file.close();
    return true;
}

void Serializer::read_bin(Group& group, std::ifstream& file) {
    // Read number of data and subgroups
    uint16_t num_data;
    file.read(reinterpret_cast<char*>(&num_data), sizeof(num_data));

    // Read data
    for (uint16_t i(0); i < num_data; ++i) {
        // Meta data
        uint8_t name_length;
        file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        std::string name(name_length, ' ');
        file.read(&name[0], name_length);

        DataType type;
        file.read(reinterpret_cast<char*>(&type), sizeof(type));

        // Actual data
        uint32_t data_size;
        file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));
        std::vector<Byte> data(data_size);
        file.read(reinterpret_cast<char*>(data.data()), data_size);

        group.data[name] = Data{type, data};
    }

    // Read subgroups
    uint16_t num_subgroups;
    file.read(reinterpret_cast<char*>(&num_subgroups), sizeof(num_subgroups));
    for (uint16_t i = 0; i < num_subgroups; ++i) {
        // Meta data
        uint8_t name_length;
        file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        std::string name(name_length, ' ');
        file.read(&name[0], name_length);

        // Recursive call
        Group& subgroup = group.subgroups[name];
        read_bin(subgroup, file);
    }
}

bool Serializer::serialize_txt(const Hierarchy& hierarchy, std::string path) {
    std::ofstream file(path + EXTENSION_TXT);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Failed to open file for text serialization: " + path);
        return false;
    }
    file << "Hierarchy: " << hierarchy.name << "\n";
    
    write_txt(hierarchy.root, file);

    file.close();
    return true;
}

void Serializer::write_txt(const Group& group, std::ofstream& file, int indent) {
    std::string indent_str(indent, ' ');
    for (const auto& [data_name, data] : group.data) {
        file << indent_str << "Data:" << data_name << " Type:" << static_cast<int>(data.type) << " Size:" << data.data.size() << " ";
        file << data_to_string(data) << "\n";
    }
    for (const auto& [subgroup_name, subgroup] : group.subgroups) {
        file << indent_str << "Group:" << subgroup_name << "\n"; 
        write_txt(subgroup, file, indent + 2);
    }
}

bool Serializer::deserialize_txt(Hierarchy& hierarchy, std::string path) {
    std::ifstream file(path + EXTENSION_TXT);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Failed to open file for text deserialization: " + path);
        return false;
    }

    // Read the name of the hierarchy
    std::string line;
    if (std::getline(file, line)) {
        if (line.rfind("Hierarchy:", 0) == 0) {
            hierarchy.name = line.substr(10);
        } else {
            Logger::instance().log(Error, "Invalid file format for text deserialization: " + path);
            file.close();
            return false;
        }
    } else {
        Logger::instance().log(Error, "Empty file for text deserialization: " + path);
        file.close();
        return false;
    }

    read_txt(hierarchy.root, file);

    file.close();
    return true;
}

/*void Serializer::read_txt(Group& group, std::ifstream& file, int level) {
    std::string line;
    while (std::getline(file, line)) {
        // Find the current line's indentation level
        int current_indent = 0;
        while (current_indent < line.size() && line[current_indent] == ' ') {
            ++current_indent;
        }
        int current_level = current_indent / 2;

        if (current_level < level) {
            // We've gone back to a higher level, so return to the previous call
            file.seekg(-static_cast<int>(line.size()) - 1, std::ios::cur); // Move back one line
            return;
        } else if (current_level > level) {
            Logger::instance().log(Error, "Invalid indentation in text deserialization");
            return;
        }

        print(line); // For debugging
        
    }
}*/

}