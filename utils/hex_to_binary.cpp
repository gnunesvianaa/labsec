#include "hex_to_binary.hpp"


string hex_to_binary(string hex){
    string binary{};

    for (char digit : hex)
    {
        if (digit >= '0' && digit <= '9')
        {
            binary += (bitset<4>(digit - '0')).to_string();
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            binary += (bitset<4>(((digit - 'a') + 10))).to_string();
        }
    }

    return binary;
}