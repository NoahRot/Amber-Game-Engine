#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <cstring>

#include "Logger/Logger.hpp"

namespace AMB {

typedef unsigned char Byte;

enum class DataType {
    INT8,
    LIST_INT8,
    INT16,
    LIST_INT16,
    INT32,
    LIST_INT32,
    UINT8,
    LIST_UINT8,
    UINT16,
    LIST_UINT16,
    UINT32,
    LIST_UINT32,
    FLOAT,
    LIST_FLOAT,
    DOUBLE,
    LIST_DOUBLE,
    BYTE,
    LIST_BYTE,
    STRING,
    UNKNOWN
};

struct Data {
    DataType type;
    std::vector<Byte> data;
};

struct Group {
    std::unordered_map<std::string, Group> subgroups;
    std::unordered_map<std::string, Data> data;

    Group& operator[](const std::string& name);

    Data& get(const std::string& name);

    bool has_data(const std::string& name) const;

    bool has_group(const std::string& name) const;
};

struct Hierarchy {
    std::string name;
    Group root;

    Group& operator[](const std::string& name);
};

void print_hierarchy(const Hierarchy& hierarchy);

void print_group(const Group& group, const std::string& name = "", int indent = 0);

std::string data_to_string(const Data& data);

template<typename T>
void get_data_info(const T& value, DataType& type, Byte*& begin, uint32_t& size_byte) {
    if constexpr (std::is_same_v<T, int8_t>) {
        type = DataType::INT8;
        begin = reinterpret_cast<Byte*>(const_cast<int8_t*>(&value));
        size_byte = sizeof(int8_t);
    } else if constexpr (std::is_same_v<T, std::vector<int8_t>>) {
        type = DataType::LIST_INT8;
        begin = reinterpret_cast<Byte*>(const_cast<int8_t*>(value.data()));
        size_byte = sizeof(int8_t) * value.size();
    } else if constexpr (std::is_same_v<T, int16_t>) {
        type = DataType::INT16;
        begin = reinterpret_cast<Byte*>(const_cast<int16_t*>(&value));
        size_byte = sizeof(int16_t);
    } else if constexpr (std::is_same_v<T, std::vector<int16_t>>) {
        type = DataType::LIST_INT16;
        begin = reinterpret_cast<Byte*>(const_cast<int16_t*>(value.data()));
        size_byte = sizeof(int16_t) * value.size();
    } else if constexpr (std::is_same_v<T, int>) {
        type = DataType::INT32;
        begin = reinterpret_cast<Byte*>(const_cast<int*>(&value));
        size_byte = sizeof(int);
    } else if constexpr (std::is_same_v<T, std::vector<int>>) {
        type = DataType::LIST_INT32;
        begin = reinterpret_cast<Byte*>(const_cast<int*>(value.data()));
        size_byte = sizeof(int) * value.size();
    } else if constexpr (std::is_same_v<T, uint8_t>) {
        type = DataType::UINT8;
        begin = reinterpret_cast<Byte*>(const_cast<uint8_t*>(&value));
        size_byte = sizeof(uint8_t);
    } else if constexpr (std::is_same_v<T, std::vector<uint8_t>>) {
        type = DataType::LIST_UINT8;
        begin = reinterpret_cast<Byte*>(const_cast<uint8_t*>(value.data()));
        size_byte = sizeof(uint8_t) * value.size();
    } else if constexpr (std::is_same_v<T, uint16_t>) {
        type = DataType::UINT16;
        begin = reinterpret_cast<Byte*>(const_cast<uint16_t*>(&value));
        size_byte = sizeof(uint16_t);
    } else if constexpr (std::is_same_v<T, std::vector<uint16_t>>) {
        type = DataType::LIST_UINT16;
        begin = reinterpret_cast<Byte*>(const_cast<uint16_t*>(value.data()));
        size_byte = sizeof(uint16_t) * value.size();
    } else if constexpr (std::is_same_v<T, uint32_t>) {
        type = DataType::UINT32;
        begin = reinterpret_cast<Byte*>(const_cast<uint32_t*>(&value));
        size_byte = sizeof(uint32_t);
    } else if constexpr (std::is_same_v<T, std::vector<uint32_t>>) {
        type = DataType::LIST_UINT32;
        begin = reinterpret_cast<Byte*>(const_cast<uint32_t*>(value.data()));
        size_byte = sizeof(uint32_t) * value.size();
    } else if constexpr (std::is_same_v<T, float>) {
        type = DataType::FLOAT;
        begin = reinterpret_cast<Byte*>(const_cast<float*>(&value));
        size_byte = sizeof(float);
    } else if constexpr (std::is_same_v<T, std::vector<float>>) {
        type = DataType::LIST_FLOAT;
        begin = reinterpret_cast<Byte*>(const_cast<float*>(value.data()));
        size_byte = sizeof(float) * value.size();
    } else if constexpr (std::is_same_v<T, double>) {
        type = DataType::DOUBLE;
        begin = reinterpret_cast<Byte*>(const_cast<double*>(&value));
        size_byte = sizeof(double);
    } else if constexpr (std::is_same_v<T, std::vector<double>>) {
        type = DataType::LIST_DOUBLE;
        begin = reinterpret_cast<Byte*>(const_cast<double*>(value.data()));
        size_byte = sizeof(double) * value.size();
    } else if constexpr (std::is_same_v<T, Byte>) {
        type = DataType::BYTE;
        begin = const_cast<Byte*>(&value);
        size_byte = sizeof(Byte);
    } else if constexpr (std::is_same_v<T, std::vector<Byte>>) {
        type = DataType::LIST_BYTE;
        begin = const_cast<Byte*>(value.data());
        size_byte = sizeof(Byte) * value.size();
    } else if constexpr (std::is_same_v<T, std::string>) {
        type = DataType::STRING;
        begin = const_cast<Byte*>(reinterpret_cast<const Byte*>(value.data()));
        size_byte = sizeof(char) * value.size();
    } else {
        type = DataType::UNKNOWN;
        begin = nullptr;
        size_byte = 0;
    }
}

template<typename T>
bool add_data(Group& group, const std::string& name, const T& value) {
    // Determine the DataType based on T
    DataType type;
    Byte* begin;
    uint32_t size_byte;
    get_data_info<T>(value, type, begin, size_byte);
    if (type == DataType::UNKNOWN || begin == nullptr || size_byte == 0) {
        Logger::instance().log(Error, "Unsupported data for serialization");
        return false;
    }

    // Check if the data with the same name already exists
    if (group.data.find(name) != group.data.end()) {
        Logger::instance().log(Warning, "Data with name '" + name + "' already exists. Overwriting.");
    }

    // Serialize the data into a byte vector
    group.data[name] = Data{type, std::vector<Byte>(begin, begin + size_byte)};

    return true;
}

template<typename T>
bool get_data(const Group& group, const std::string& name, T& value) {
    // Find the data by name
    auto it = group.data.find(name);
    if (it == group.data.end()) {
        Logger::instance().log(Error, "Data with name '" + name + "' not found.");
        return false;
    }

    const Data& data = it->second;

    // Determine the expected DataType based on T
    DataType expected_type;
    Byte* begin;
    uint32_t size_byte;
    get_data_info<T>(value, expected_type, begin, size_byte);
    if (expected_type == DataType::UNKNOWN) {
        Logger::instance().log(Error, "Unsupported data type for deserialization");
        return false;
    }

    // Check if the types match
    if (data.type != expected_type) {
        Logger::instance().log(Error, "Data type mismatch for '" + name + "'. Expected type: " + std::to_string(static_cast<int>(expected_type)) + ", but got: " + std::to_string(static_cast<int>(data.type)));
        return false;
    }

    // Check if it is a list type and resize if necessary
    if (data.type != expected_type) {
        Logger::instance().log(Error, "Data type mismatch for '" + name + "'. Expected type: " + std::to_string(static_cast<int>(expected_type)) + ", but got: " + std::to_string(static_cast<int>(data.type)));
        return false;
    }

    // Deserialize the byte vector back into the original type
    if constexpr (
        std::is_same_v<T, std::vector<int>> ||
        std::is_same_v<T, std::vector<float>> ||
        std::is_same_v<T, std::vector<double>> ||
        std::is_same_v<T, std::vector<Byte>>
    ) {
        value.resize(data.data.size() / sizeof(typename T::value_type));
        std::memcpy(reinterpret_cast<void*>(value.data()), data.data.data(), data.data.size());
    } else if constexpr (std::is_same_v<T, std::string>) {
        value.resize(data.data.size() / sizeof(char));
        std::memcpy(reinterpret_cast<void*>(value.data()), data.data.data(), data.data.size());
    } else {
        std::memcpy(reinterpret_cast<void*>(&value), data.data.data(), sizeof(T));
    }

    return true;
}

}