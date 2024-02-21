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
#include "../utils/file_to_string.hpp"

using namespace std;

string break_repeating_key_xor(string file_path);
vector<unsigned  char> base64_to_bytes(string text);
int hamming_distance(const std::vector<unsigned char>& string_byte_1, const std::vector<unsigned char>& string_byte_2);

#endif
