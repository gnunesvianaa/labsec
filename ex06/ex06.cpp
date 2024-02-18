#include "ex06.hpp"

string ex06()
{
    // it's been base64'd after being encrypted with repeating-key XOR.
    string texto = decodeBase64File("/Users/gustavonunesviana/Desktop/preDesafioLabsec/ex06/encripted64.txt");

    int keysize{};
    float best_score{};
    // achar o KEYSIZE ft
    // for (size_t key_length{2}; key_length <= 40; key_length++)
    // {
    //     //pegar quatro amostras
    //     string amostra1 = texto.substr(0, key_length);
    //     string amostra2 = texto.substr(key_length, key_length);
    //     // tdodas as combinacoes entre as qutatro dois a dois 

    //     float score = hammingDistance(amostra1, amostra2) / key_length;

    //     if (score > best_score)
    //     {
    //         best_score = score;
    //         keysize = key_length;
    //     }
    // }
    // cout << keysize << endl;
    //ex2 bytes xor
    //mesma coisa do ex tres
    //reapting key ex05
    return "terminando";
}

int hammingDistance(string text1, string text2)
{
    try
    {
        if (text1.size() != text2.size())
        {
            throw string("as entradas da hammingDistance must be equal");
        }

        // conta os differing_bits
        int differing_bits{};

        for (size_t i{}; i < text1.size(); i++)
        {
            std::bitset<8> binary_text1_char(text1[i]);
            std::bitset<8> binary_text2_char(text2[i]);

            std::bitset<8> binary_result = binary_text1_char ^ binary_text2_char;

            for (size_t i{}; i < 8; i++)
            {
                if (binary_result[i] == 1)
                {
                    differing_bits++;
                }
            }
        }

        return differing_bits;
    }
    catch (const string error)
    {
        cerr << "error: " << error << endl;
        return -1;
    }
}

string decodeBase64File(string source) {
    // extracao do texto
    std::ifstream arquivo(source);
    string texto64;
    string linha;
    while (getline(arquivo, linha))
    {
        texto64 += linha;
    }
    arquivo.close();

    // dicionario
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int val = 0, valb = -8;

    vector<unsigned char> decoded_text{};

    for (char c: texto64){
        if(c == '='){
            break;
        }
        val = (val << 6) + base64_chars.find(c);   
        valb += 6;
        cout << "char c: " << c << endl;
        cout << "val: " << val << endl;
        cout << "val << 6: " << (val << 6) << endl;
        cout << "val dict: " << base64_chars.find(c) << endl;
        cout << "valb: " << valb << endl;
        break;

    }

    return string(decoded_text.begin(), decoded_text.end());
}