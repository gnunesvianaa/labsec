#include "fixed_xor.hpp"

// implementacao do XOR bit a bit 
string fixed_xor(string hex1, string hex2)
{
    // hex to binary
    string binary1{};

    // utilizo a propriedade de char e tabela ascii
    for (char digit : hex1)
    {
        if (digit >= '0' && digit <= '9')
        {
            binary1 += (bitset<4>(digit - '0')).to_string();
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            binary1 += (bitset<4>(((digit - 'a') + 10))).to_string();
        }
    }

    // hex to binary
    string binary2{};

    // utilizo a propriedade de char e tabela ascii
    for (char digit : hex2)
    {
        if (digit >= '0' && digit <= '9')
        {
            binary2 += (bitset<4>(digit - '0')).to_string();
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            binary2 += (bitset<4>(((digit - 'a') + 10))).to_string();
        }
    }

    // xor
    string binary_xor{};
    for (size_t i{}; i < binary1.size(); i++)
    {
        binary_xor += to_string((binary1[i] - '0') ^ (binary2[i] - '0'));
    }

    // binary_xor to hex_xor
    string hex_xor;

    // crio um binary vector
    vector<string> binary_vector;
    for (size_t i{}; i < (binary_xor.size() / 4); i++)
    {
        binary_vector.push_back(binary_xor.substr((i * 4), 4));
    }

    // constante de conversao
    static const string hex_conversao = "0123456789abcdef";

    // conversao
    for (string i : binary_vector)
    {
        int decimal = std::stoi(i, nullptr, 2);
        hex_xor += hex_conversao[decimal];
    }
    return hex_xor;
}