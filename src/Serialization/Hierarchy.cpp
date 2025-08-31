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

Group& Hierarchy::operator[](const std::string& name) {
    return root[name];
}

void print_hierarchy(const Hierarchy& hierarchy) {
    std::cout << "Hierarchy: " << hierarchy.name << "\n";
    print_group(hierarchy.root, "<Root>", 0);
}

void print_group(const Group& group, const std::string& name, int indent) {
    std::cout << std::string(indent, ' ') << "Group: " << name << "\n";
    for (const auto& [data_name, data] : group.data) {
        std::cout << std::string(indent + 2, ' ') << "Data: " << data_name << " (Type: " << static_cast<int>(data.type) << ", Size: " << data.data.size() << " bytes) : ";
        std::cout << data_to_string(data) << "\n";
    }
    for (const auto& [subgroup_name, subgroup] : group.subgroups) {
        print_group(subgroup, subgroup_name, indent + 2);
    }
}

std::string data_to_string(const Data& data) {
    
    switch (data.type)
    {
    case DataType::INT8:
        if (data.data.size() == sizeof(int8_t)) {
            int8_t value;
            std::memcpy(&value, data.data.data(), sizeof(int8_t));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_INT8:
        {
            size_t count = data.data.size() / sizeof(int8_t);
            std::vector<int8_t> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::INT16:
        if (data.data.size() == sizeof(int16_t)) {
            int16_t value;
            std::memcpy(&value, data.data.data(), sizeof(int16_t));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_INT16:
        {
            size_t count = data.data.size() / sizeof(int16_t);
            std::vector<int16_t> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::INT32:
        if (data.data.size() == sizeof(int)) {
            int value;
            std::memcpy(&value, data.data.data(), sizeof(int));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_INT32:
        {
            size_t count = data.data.size() / sizeof(int);
            std::vector<int> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::UINT8:
        if (data.data.size() == sizeof(uint8_t)) {
            uint8_t value;
            std::memcpy(&value, data.data.data(), sizeof(uint8_t));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_UINT8:
        {
            size_t count = data.data.size() / sizeof(uint8_t);
            std::vector<uint8_t> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::UINT16:
        if (data.data.size() == sizeof(uint16_t)) {
            uint16_t value;
            std::memcpy(&value, data.data.data(), sizeof(uint16_t));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_UINT16:
        {
            size_t count = data.data.size() / sizeof(uint16_t);
            std::vector<uint16_t> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::UINT32:
        if (data.data.size() == sizeof(uint32_t)) {
            uint32_t value;
            std::memcpy(&value, data.data.data(), sizeof(uint32_t));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_UINT32:
        {
            size_t count = data.data.size() / sizeof(uint32_t);
            std::vector<uint32_t> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::FLOAT:
        if (data.data.size() == sizeof(float)) {
            float value;
            std::memcpy(&value, data.data.data(), sizeof(float));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_FLOAT:
        {
            size_t count = data.data.size() / sizeof(float);
            std::vector<float> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::DOUBLE:
        if (data.data.size() == sizeof(double)) {
            double value;
            std::memcpy(&value, data.data.data(), sizeof(double));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_DOUBLE:
        {
            size_t count = data.data.size() / sizeof(double);
            std::vector<double> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::BYTE:
        if (data.data.size() == sizeof(Byte)) {
            Byte value;
            std::memcpy(&value, data.data.data(), sizeof(Byte));
            return std::to_string(value);
        }
        break;

    case DataType::LIST_BYTE:
        {
            size_t count = data.data.size() / sizeof(Byte);
            std::vector<Byte> values(count);
            std::memcpy(values.data(), data.data.data(), data.data.size());
            std::string result = "";
            for (const auto& v : values) {
                result += std::to_string(v) + " ";
            }
            return result;
        }
        break;

    case DataType::STRING:
        {
            std::string value(data.data.begin(), data.data.end());
            return value;
        }
        break;

    default:
        return "<Unknown Data Type>";
        break;
    }

    return "<Unknown Data Type>";
}

}