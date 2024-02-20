#include "detect_single_character_xor.hpp"

string detect_single_character_xor(string file_path)
{
    // extracting each line
    std::ifstream arquivo(file_path);

    if (!arquivo.is_open()) {
        return "is was not possible to open the file";
    }

    vector<string> lines_encrypted;
    string linha;
    while (getline(arquivo, linha))
    {
        lines_encrypted.push_back(linha);
    }
    
    // deciphering each line
    vector<string> lines_decripted;
    for (string linha : lines_encrypted)
    {
        lines_decripted.push_back(single_byte_xor_cipher(linha));
    }

    // comparing decripted lines
    string saida = compare_texts(lines_decripted);

    arquivo.close();

    return saida;  
}

string compare_texts(vector<string> texts) {   
    vector<int> scores(texts.size(), 100);

    for (size_t i{}; i < (texts.size()); i++)
    {
        std::map<std::string, int> quantities = {
            {"lowercase", 0}, // abc
            {"uppercase", 0}, // ABC
            {"space", 0},     //
            {"common", 0},    //.,
            {"rare", 0},      //?!"()?:123
            {"useless", 0}    //\n@#$%^&*
        };

        bool no_printable{false};
        
        for (char &c : texts[i]) {
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
            scores[i] = 0;
            continue;
        }
        // calculating score
        int length = texts.size();
        scores[i] += ((static_cast<double>(quantities["space"]) / length) * 100) * 20;    // most important for a sentence
        scores[i] += ((static_cast<double>(quantities["lowercase"]) / length) * 100) * 10;
        scores[i] += ((static_cast<double>(quantities["uppercase"]) / length) * 100) * 2;
        scores[i] += ((static_cast<double>(quantities["common"]) / length) * 100) * 1.9;
        scores[i] += ((static_cast<double>(quantities["rare"]) / length) * 100) * 1.2;
        scores[i] -= ((static_cast<double>(quantities["useless"]) / length) * 100) * 3;   // least important for a sentence
    }
    
    // finding index of the best text
    auto it_resposta = max_element(scores.begin(), scores.end());
    int indice = distance(scores.begin(), it_resposta);

    return texts[indice];
}