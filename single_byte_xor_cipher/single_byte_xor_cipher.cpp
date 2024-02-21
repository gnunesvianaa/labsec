#include "single_byte_xor_cipher.hpp"

string single_byte_xor_cipher(string encripted_hex) {
    if (((encripted_hex.size()) % 2) != 0) {
        encripted_hex = to_string(0) + encripted_hex;
    }

    vector<unsigned char> bytes = hex_to_bytes(encripted_hex);

    int key = find_key(bytes);

    for (unsigned char &c : bytes){
        c ^= key;
    }

    string str;
    for (unsigned char byte : bytes) {
        str += byte;
    }

    return str;
}

int find_key(vector<unsigned char> bytes) {
    vector<int> scores(128, 100);
 
    for (size_t key{}; key < 128; key++) {
        vector<unsigned char> decrypted_bytes = bytes;
        for (unsigned char &c : decrypted_bytes) {
            c ^= key;
        }

        std::map<std::string, int> quantities = {
            {"lowercase", 0}, // abc
            {"uppercase", 0}, // ABC
            {"space", 0},     //
            {"common", 0},    //.,
            {"rare", 0},      //?!"()?:123
            {"useless", 0},    //\n@#$%^&*
            {"unprintable", 0}
        };

        for (unsigned char c : decrypted_bytes) {
            if ((((c <= 6) || (14 <= c)) && (c <= 31)) || (c == 127)) {
                quantities["unprintable"]++;
            } else if ((c >= 97) && (c <= 122)) {
                quantities["lowercase"]++;
            } else if ((c >= 65) && (c <= 90)) {
                quantities["uppercase"]++;
            } else if (c == 32) {
                quantities["space"]++;
            } else if ((c == 44) || (c == 46)) {
                quantities["common"]++;
            } else if ((c == 33) || (c == 34) || (c == 40) || (c == 41) || (c == 45) || (c == 58) || (c == 63) || ((c >= 48) && (c <= 57))) {
                quantities["rare"]++;
            } else {
                quantities["useless"]++;
            }
        };

        // calculating score
        int length = decrypted_bytes.size();
        scores[key] += ((static_cast<double>(quantities["space"]) / length) * 100) * 10;    // most important for a sentence
        scores[key] += ((static_cast<double>(quantities["lowercase"]) / length) * 100) * 1000;
        scores[key] += ((static_cast<double>(quantities["uppercase"]) / length) * 100) * 2;
        scores[key] += ((static_cast<double>(quantities["common"]) / length) * 100) * 1.9;
        scores[key] += ((static_cast<double>(quantities["rare"]) / length) * 100) * 1.2;
        scores[key] -= ((static_cast<double>(quantities["useless"]) / length) * 100) * 3;
        scores[key] -= ((static_cast<double>(quantities["useless"]) / length) * 100) * 100;   // least important for a sentence
    }

    // finding best key
    auto it_answer = max_element(scores.begin(), scores.end());
    int key = distance(scores.begin(), it_answer);

    return key;
}

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