#ifndef DETECT_AES_IN_ECB_MODE_HPP
#define DETECT_AES_IN_ECB_MODE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <unordered_set>
#include "../utils/file_to_string.hpp"
#include "../utils/hex_to_bytes.hpp"

using namespace std;

string detect_aes_in_ecb_mode(string file_path);

#endif
