#include "single_byte_xor_cipher.hpp"

string single_byte_xor_cipher(string encripted_hex) {
    // make mutiple of 2
    if (((encripted_hex.size()) % 2) != 0) {
        encripted_hex = to_string(0) + encripted_hex;
    }

    vector<unsigned char> bytes = hex_to_bytes(encripted_hex);

    // find key and return the deciphered text
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
    // scoring system that loop for every key to estimate the best one
    vector<int> scores(128, 100);
 
    for (size_t key{}; key < 128; key++) {
        vector<unsigned char> decrypted_bytes = bytes;
        for (unsigned char &c : decrypted_bytes) {
            c ^= key;
        }

        // stores the quantity of a character in categories
        map<string, int> char_categories = calculate_char_categories(string(decrypted_bytes.begin(), decrypted_bytes.end()));
        
        // calculate score using scoring weight
        scores[key] += char_categories["lower"]   * 1000; // most important for a text
        scores[key] += char_categories["space"]   *  100;
        scores[key] += char_categories["upper"]   *   30;
        scores[key] += char_categories["punct"]   *   20;
        scores[key] += char_categories["digit"]   *   10;
        scores[key] += char_categories["other"]   *    1;
        scores[key] -= char_categories["cntrl"]   *  500;
        scores[key] -= char_categories["unprint"] * 1000; // least important for a text
    }

    // return the best key
    auto it_answer = max_element(scores.begin(), scores.end());
    int key = distance(scores.begin(), it_answer);

    return key;
}