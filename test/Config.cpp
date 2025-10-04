#include "Configuration/Configuration.hpp"

#include "Serialization/Hierarchy.hpp"

void read_txt(AMB::Group& group, std::ifstream& file, int level = 0) {
    std::string line;
    while (std::getline(file, line)) {

        // Find the current line's indentation level
        int current_indent = 0; 
        while (current_indent < line.size() && line[current_indent] == ' ') {
            ++current_indent;
        }
        int current_level = current_indent / 2;

        std::cout << line << std::endl;

        // This line is a subgroup or data of the current group
        std::string content = line.substr(current_indent);
        //std::cout << "Content substr: " << content.substr(0,5) << std::endl;
        if (content.size() >= 5 && content.substr(0,5) == "Group") {
            // It's a subgroup
            std::string group_name = content.substr(6); // Remove "Group " and ":"
            AMB::Group& subgroup = group[group_name];
            //std::cout << "Reading subgroup: " << group_name << std::endl;
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
            AMB::DataType data_type = static_cast<AMB::DataType>(std::stoi(type_str));
            data_content = data_content.substr(colon_pos + 1);

            // Find the size
            data_content = data_content.substr(5); // Remove "Size:"
            colon_pos = data_content.find(' ');
            std::string size_str = data_content.substr(0, colon_pos);
            size_t data_size = static_cast<size_t>(std::stoul(size_str));
            data_content = data_content.substr(colon_pos + 1);

            std::cout << "Reading data: " << data_name << " Type: " << static_cast<int>(data_type) << " Size: " << data_size << std::endl;
        }

        //read_txt(group, file, level);
    }
}

int main(int argc, char* argv[]) {

    AMB::Configuration& config = AMB::Configuration::instance();
    config.set_win_title("Changed Title");
    config.set_win_height(720);
    config.set_win_width(1280);

    config.initialize();
    config.save_configuration("test/config");

    config.load_configuration("test/config");

    AMB::Hierarchy config_hierarchy = config.config_to_hierarchy();

    AMB::Serializer serializer;
    serializer.serialize_txt(config_hierarchy, "test/config");

    AMB::Hierarchy new_hierarchy;
    //serializer.deserialize_txt(new_hierarchy, "test/config");
    std::ifstream file("test/config.amber_txt");
    read_txt(new_hierarchy.root, file);
    AMB::print_hierarchy(new_hierarchy);


    return 0;
}