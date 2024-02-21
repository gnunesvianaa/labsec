#ifndef DETECT_SINGLE_CHARACTER_XOR_HPP
#define DETECT_SINGLE_CHARACTER_XOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "../single_byte_xor_cipher/single_byte_xor_cipher.hpp"
#include "../utils/calcule_char_categories.hpp"

using namespace std;

string detect_single_character_xor(string file_path);
string compare_texts(vector<string> texts);

#endif
