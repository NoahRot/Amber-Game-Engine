#include "Serialization/Hierarchy.hpp"

namespace AMB {

Group& Group::operator[](const std::string& name) {
    return subgroups[name];
}

Data& Group::get(const std::string& name) {
    return data[name];
}

bool Group::has_data(const std::string& name) const {
    return data.find(name) != data.end();
}

bool Group::has_group(const std::string& name) const {
    return subgroups.find(name) != subgroups.end();
}

void print_group(const Group& group, const std::string& name, int indent) {
    std::cout << std::string(indent, ' ') << "Group: " << name << "\n";
    for (const auto& [data_name, data] : group.data) {
        std::cout << std::string(indent + 2, ' ') << "Data: " << data_name << " (Type: " << static_cast<int>(data.type) << ", Size: " << data.data.size() << " bytes)\n";
    }
    for (const auto& [subgroup_name, subgroup] : group.subgroups) {
        print_group(subgroup, subgroup_name, indent + 2);
    }
}

}