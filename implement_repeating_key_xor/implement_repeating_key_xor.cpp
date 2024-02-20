#include "implement_repeating_key_xor.hpp"

string implement_repeating_key_xor(string text, string key)
{
    int count_key = 0;
    for (char &c : text)
    {
        c = static_cast<int>(c) ^ static_cast<int>(key[count_key]);
        count_key++;
        if (count_key == key.size()){
            count_key = 0;
        }
    }

    // convert to hex
    stringstream hex;
    
    for (char c : text) {
        hex << std::hex << setw(2) << std::setfill('0') << static_cast<int>(c);
    }

    return hex.str();

}
