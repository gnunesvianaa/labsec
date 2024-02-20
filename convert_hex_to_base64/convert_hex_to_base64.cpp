#include "convert_hex_to_base64.hpp"

// transformacao de hexadecimal para base 64
string convert_hex_to_base64(string hex)
{
    // hex to binary
    string binary{};

    // utilizo a propriedade de char e tabela ascii
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

    // tor no binary multiplo de 6
    while ((binary.size() % 6) != 0)
    {
        binary = '0' + binary;
    }

    // crio um binary vector com os elementos binario de seis digitos
    vector<string> binary_vector;
    for (size_t i{}; i < (binary.size() / 6); i++)
    {
        binary_vector.push_back(binary.substr((i * 6), 6));
    }

    // binary to base 64
    string base64;

    // constante de conversao
    static const string base64_conversao = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // transformacao
    for (string i : binary_vector)
    {
        int decimal = std::stoi(i, nullptr, 2);
        base64 += base64_conversao[decimal];
    }
    return base64;
}