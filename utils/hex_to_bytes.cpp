#include "hex_to_bytes.hpp"

vector<unsigned char> hex_to_bytes(const string& encripted_hex) {
    vector<unsigned char> bytes;

    for (size_t i = 0; i < encripted_hex.size(); i += 2) {
        string byte_str = encripted_hex.substr(i, 2);

        unsigned int byte_value;
        std::stringstream ss(byte_str);
        ss >> std::hex >> byte_value;

        // Check if conversion was successful (avoid storing invalid bytes)
        if (!ss.fail() && byte_value <= 255) { 
            bytes.push_back(static_cast<unsigned char>(byte_value));
        } else {
            // Handle conversion errors here (e.g., throw an exception)
            std::cerr << "Error converting hex byte: " << byte_str << std::endl;
        }
    }

    return bytes;
}