#include "convert_hex_to_base64.hpp"

string convert_hex_to_base64(string hex) {
    string binary = hex_to_binary(hex);

    // make multiple of 6
    while ((binary.size() % 6) != 0){
        binary = '0' + binary;
    }

    // put it into a vector
    vector<string> binary_vector;
    for (size_t i{}; i < (binary.size() / 6); i++) {
        binary_vector.push_back(binary.substr((i * 6), 6));
    }

    // convert to base 64
    string base64;

    static const string base64_conversion = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (string i : binary_vector) {
        int decimal = stoi(i, nullptr, 2);
        base64 += base64_conversion[decimal];
    }
    
    return base64;
}