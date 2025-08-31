#include "Serialization/Hierarchy.hpp"
#include "Serialization/Serializer.hpp"

int main(int argc, char* argv[]) {

    int a = 3;
    std::vector<float> vec = {1.0f, 2.0f, 3.0f};
    std::vector<float> vec_ = {4.0f, 5.0f, 6.0f};
    std::string str = "Hello, World!";

    AMB::Hierarchy root;

    AMB::add_data(root["number"]["int_value"], "my_int", a);
    AMB::add_data(root["number"]["float_list"], "my_floats", vec);
    AMB::add_data(root["number"]["float_list"], "my_floats_r", vec_);
    AMB::add_data(root["text"]["greeting"], "my_string", str);

    AMB::print_hierarchy(root);

    int a2=0;
    std::vector<float> vec2(3);
    std::vector<float> vec2r;
    std::string str2(' ', 8);
    AMB::get_data(root["number"]["int_value"], "my_int", a2);
    AMB::get_data(root["number"]["float_list"], "my_floats", vec2);
    AMB::get_data(root["number"]["float_list"], "my_floats_r", vec2r);
    AMB::get_data(root["text"]["greeting"], "my_string", str2);
    std::cout << "Deserialized int: " << a2 << std::endl;
    std::cout << "Deserialized vec: ";
    for (const auto& f : vec2) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
    std::cout << "Deserialized vec_: ";
    for (const auto& f : vec2r) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
    std::cout << "Deserialized str: " << str2 << std::endl;

    AMB::Serializer serializer;
    serializer.serialize_bin(root, "test");

    AMB::Hierarchy loaded;
    serializer.deserialize_bin(loaded, "test"); 
    AMB::print_hierarchy(loaded);

    AMB::get_data(loaded["number"]["int_value"], "my_int", a2);
    AMB::get_data(loaded["number"]["float_list"], "my_floats", vec2);
    AMB::get_data(root["number"]["float_list"], "my_floats_r", vec2r);
    AMB::get_data(loaded["text"]["greeting"], "my_string", str2);
    std::cout << "Deserialized int: " << a2 << std::endl;
    std::cout << "Deserialized vec: ";
    for (const auto& f : vec2) {
        std::cout << f << " "; 
    }
    std::cout << std::endl;
    std::cout << "Deserialized vec_: ";
    for (const auto& f : vec2r) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
    std::cout << "Deserialized str: " << str2 << std::endl;

    return 0;
}