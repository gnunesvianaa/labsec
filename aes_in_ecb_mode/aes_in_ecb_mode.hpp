#ifndef AES_IN_ECB_MODE_HPP
#define AES_IN_ECB_MODE_HPP

#include <openssl/evp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include "../utils/file_to_string.hpp"

using namespace std;

string aes_in_ecb_mode(string file_path, string key);
std::string base64_decode(const std::string &input);

#endif
