#include "single_byte_xor_cipher.hpp"

string single_byte_xor_cipher(string encripted_hex)
{
    // check formatting
    if (((encripted_hex.size()) % 2) != 0)
    {
        encripted_hex = to_string(0) + encripted_hex;
    }

    // hex to text
    string text_encripted;
    for (size_t i{}; i < encripted_hex.size(); i += 2)
    {
        string byte = encripted_hex.substr(i, 2);

        int decimal;
        istringstream(byte) >> std::hex >> decimal;

        text_encripted += static_cast<char>(decimal);
    }

    // storing each score
    vector<int> scores(128, 100);
 
    for (size_t key{}; key < 128; key++) {
        string text = text_encripted;

        std::map<std::string, int> quantities = {
            {"lowercase", 0}, // abc
            {"uppercase", 0}, // ABC
            {"space", 0},     //
            {"common", 0},    //.,
            {"rare", 0},      //?!"()?:123
            {"useless", 0}    //\n@#$%^&*
        };

        bool no_printable{false};

        for (char &c : text) {
            c = static_cast<int>(c) ^ static_cast<int>(key);

            int int_c = static_cast<int>(c);

            if ((((int_c <= 6) || (14 <= int_c)) && (int_c <= 31)) || (int_c == 127)) {
                no_printable = true;
                break;
            } else if ((int_c >= 97) && (int_c <= 122)) {
                quantities["lowercase"]++;
            } else if ((int_c >= 65) && (int_c <= 90)) {
                quantities["uppercase"]++;
            } else if (int_c == 32) {
                quantities["space"]++;
            } else if ((int_c == 44) || (int_c == 46)) {
                quantities["common"]++;
            } else if ((int_c == 33) || (int_c == 34) || (int_c == 40) || (int_c == 41) || (int_c == 45) || (int_c == 58) || (int_c == 63) || ((int_c >= 48) && (int_c <= 57))) {
                quantities["rare"]++;
            } else {
                quantities["useless"] += 1;
            }
        };

        if (no_printable)
        {
            scores[key] = 0;
            continue;
        }

        // calculating score
        int length = text.size();
        scores[key] += ((static_cast<double>(quantities["space"]) / length) * 100) * 20;    // most important for a sentence
        scores[key] += ((static_cast<double>(quantities["lowercase"]) / length) * 100) * 10;
        scores[key] += ((static_cast<double>(quantities["uppercase"]) / length) * 100) * 2;
        scores[key] += ((static_cast<double>(quantities["common"]) / length) * 100) * 1.9;
        scores[key] += ((static_cast<double>(quantities["rare"]) / length) * 100) * 1.2;
        scores[key] -= ((static_cast<double>(quantities["useless"]) / length) * 100) * 3;   // least important for a sentence
    }

    // return the best answer
    auto it_answer = max_element(scores.begin(), scores.end());
    int index = distance(scores.begin(), it_answer);

    string text_decripted = text_encripted;

    for (char &c : text_decripted)
    {
        c = static_cast<int>(c) ^ static_cast<int>(index);
    }

    return text_decripted;
}
int find_key(string text) {

}

