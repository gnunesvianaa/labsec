#ifndef BREAK_REAPTING_KEY_XOR_HPP
#define BREAK_REAPTING_KEY_XOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include "../single_byte_xor_cipher/single_byte_xor_cipher.hpp"

using namespace std;

string break_repeating_key_xor(string file_path);
vector<unsigned  char> convert_base64_file_to_bytes(const string& file_path);
vector<unsigned  char> string_to_byte_vector(const std::string& str);
int hamming_distance(const std::vector<unsigned char>& string_byte_1, const std::vector<unsigned char>& string_byte_2);

#endif
