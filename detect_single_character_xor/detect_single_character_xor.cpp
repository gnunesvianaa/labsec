#include "detect_single_character_xor.hpp"

string detect_single_character_xor(string file_path)
{
    // extracting each line
    ifstream file(file_path);

    if (!file.is_open()) {
        return "is was not possible to open the file";
    }

    vector<string> lines_encrypted;
    string line;
    while (getline(file, line)) {
        lines_encrypted.push_back(line);
    }
    
    // deciphering each line
    vector<string> lines_decripted;
    for (string line : lines_encrypted) {
        lines_decripted.push_back(single_byte_xor_cipher(line));
    }

    // comparing decripted lines
    string saida = compare_texts(lines_decripted);

    file.close();

    return saida;  
}

string compare_texts(vector<string> texts) { 
    // storing a score for evey text
    vector<int> scores(texts.size(), 100);

    for (size_t i{}; i < (texts.size()); i++) {
        map<string, int> char_categories = calculate_char_categories(texts[i]);

        // calculate score using scoring weight
        scores[i] += char_categories["lower"]   * 1000; // most important for a text
        scores[i] += char_categories["space"]   *  100;
        scores[i] += char_categories["upper"]   *   30;
        scores[i] += char_categories["punct"]   *   20;
        scores[i] += char_categories["digit"]   *   10;
        scores[i] += char_categories["other"]   *    1;
        scores[i] -= char_categories["cntrl"]   *  500;
        scores[i] -= char_categories["unprint"] * 1000; // least important for a text
    }
    
    // return the best text
    auto it_answer = max_element(scores.begin(), scores.end());
    int index = distance(scores.begin(), it_answer);

    return texts[index];
}