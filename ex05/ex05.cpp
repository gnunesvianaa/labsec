#include "ex05.hpp"

// implementacao do xor com chave reptida
string ex05(string text, string key)
{
    // conversap dos caracteres
    int count_key = 0;
    for (char &c : text)
    {
        c = static_cast<int>(c) ^ static_cast<int>(key[count_key]);
        count_key++;
        if (count_key == key.size()){
            count_key = 0;
        }
    }

    stringstream hex;
    
    for (char c : text) {
        hex << std::hex << setw(2) << std::setfill('0') << static_cast<int>(c);
    }

    // Convert the stringstream to a string and return
    return hex.str();

}
