#include "single_byte_xor_cipher.hpp"

// implementacao do xor cipher
string single_byte_xor_cipher(string encripted_hex)
{
    // checar formatacao byte
    if (((encripted_hex.size()) % 2) != 0)
    {
        encripted_hex = to_string(0) + encripted_hex;
    }

    // hex to text
    string text_encripted;
    for (size_t i{}; i < encripted_hex.size(); i += 2)
    {
        string byte = encripted_hex.substr(i, 2);

        // hex to integer
        int decimal;
        istringstream(byte) >> std::hex >> decimal;

        text_encripted += static_cast<char>(decimal);
    }

    // vetor para armazenar as pontuacoes de cada chave
    vector<int> scores(128, 100);

    // loop por cada uma de todas as possiveis chaves
    for (size_t key{}; key < 128; key++)
    {
        string text_decripted = text_encripted;

        // quantizacao
        std::map<std::string, int> quantidades = {
            {"minusculo", 0}, // abc
            {"maiusculo", 0}, // abc
            {"espaco", 0},    //
            {"comum", 0},     //.,
            {"raro", 0},      //?!"()?:123
            {"inutil", 0}     //\n@#$%^&*
        };

        bool no_printable{false};

        // avaliar frequencias
        for (char &c : text_decripted)
        {
            c = static_cast<int>(c) ^ static_cast<int>(key);

            int int_c = static_cast<int>(c);
            // sinais nao imprimiveis
            if (((int_c != 0) && (int_c <= 6) && (14 >= int_c) &&
                 (int_c != 29) && (int_c < 32)) || (int_c == 127))
            {
                no_printable = true;
                break;
            }
            else if ((int_c >= 97) && (int_c <= 122))
            {
                quantidades["minusculo"]++;
            }
            else if ((int_c >= 65) && (int_c <= 90))
            {
                quantidades["maiusculo"]++;
            }
            else if (int_c == 32)
            {
                quantidades["espaco"]++;
            }
            else if ((int_c == 44) || (int_c == 46))
            {
                quantidades["comum"]++;
            }
            else if (
                (int_c == 33) || (int_c == 34) || (int_c == 40) || (int_c == 41) || 
                (int_c == 45) || (int_c == 58) || (int_c == 63) || ((int_c >= 48) && (int_c <= 57)))
            {
                quantidades["raro"]++;
            }
            else
            {
                quantidades["inutil"] += 1;
            }
        };
        if (no_printable)
        {
            scores[key] = 0;
            continue;
        }

        // calculo da pontuacao segundo frequencia
        int length = text_decripted.size();
        scores[key] += ((static_cast<double>(quantidades["espaco"]) / length) * 100) * 20; // mais importante para existencia da frase
        scores[key] += ((static_cast<double>(quantidades["minusculo"]) / length) * 100) * 10;
        scores[key] += ((static_cast<double>(quantidades["maiusculo"]) / length) * 100) * 2;
        scores[key] += ((static_cast<double>(quantidades["comum"]) / length) * 100) * 1.9;
        scores[key] += ((static_cast<double>(quantidades["raro"]) / length) * 100) * 1.2;
        scores[key] -= ((static_cast<double>(quantidades["inutil"]) / length) * 100) * 3;  // menos importante para existencia da frase
    }

    // encontrando indice
    auto it_resposta = max_element(scores.begin(), scores.end());
    int indice = distance(scores.begin(), it_resposta);

    // rascunho pra resposta
    string text_decripted = text_encripted;

    // conversap dos caracteres
    for (char &c : text_decripted)
    {
        c = static_cast<int>(c) ^ static_cast<int>(indice);
    }
    return text_decripted;
}