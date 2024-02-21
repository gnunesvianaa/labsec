#include "file_to_string.hpp"

string file_to_string(string file_path){
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "error: could not open file '" << file_path << "'" << std::endl;
        return {};
    }

    std::string text, line;
    while (std::getline(file, line)) {
        text += line;
    }
    file.close();

    return text;
}