#include "fixed_xor.hpp"

string fixed_xor(string hex_1, string hex_2){
    string binary_1 = hex_to_binary(hex_1);
    string binary_2 = hex_to_binary(hex_2);

    // xor
    string binary_xor{};
    for (size_t i{}; i < binary_1.size(); i++)
    {
        binary_xor += to_string((binary_1[i] - '0') ^ (binary_2[i] - '0'));
    }

    // binary_xor to hex_xor
    string hex_xor;

    vector<string> binary_vector;
    for (size_t i{}; i < (binary_xor.size() / 4); i++) {
        binary_vector.push_back(binary_xor.substr((i * 4), 4));
    }

    static const string hex_conversion = "0123456789abcdef";

    for (string i : binary_vector) {
        int decimal = std::stoi(i, nullptr, 2);
        hex_xor += hex_conversion[decimal];
    }
    
    return hex_xor;
}