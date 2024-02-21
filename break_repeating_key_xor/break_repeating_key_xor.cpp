#include "break_repeating_key_xor.hpp"

string break_repeating_key_xor(string file_path)
{   
    vector<unsigned char> byte_vector = convert_base64_file_to_bytes(file_path);

    int min_edit_distance;
    int best_keysize;

    for (size_t KEYSIZE{2}; KEYSIZE <= 40; KEYSIZE++) {
        vector<unsigned char> sample_1(byte_vector.begin(), byte_vector.begin() + (KEYSIZE*50));
        vector<unsigned char> sample_2(byte_vector.begin() + (KEYSIZE * 50), byte_vector.begin() + 100 * KEYSIZE);

        int edit_distance = hamming_distance(sample_1, sample_2)/KEYSIZE;

        if (KEYSIZE == 2){
            min_edit_distance = edit_distance;
            best_keysize = 2;
            continue;
        }
        if (edit_distance < min_edit_distance){
            min_edit_distance = edit_distance;
            best_keysize = KEYSIZE;
        }
    }

    vector<vector<unsigned char>> blocks;
    int block_size = best_keysize;

    for (size_t i = 0; i < byte_vector.size(); i += block_size) {
        
        int current_block_size = std::min(block_size, static_cast<int>(byte_vector.size() - i));
        vector<unsigned char> block(byte_vector.begin() + i, byte_vector.begin() + i + current_block_size); 
        blocks.push_back(block);
    }

    vector<vector<unsigned char>> transposed_blocks;
    for (int i = 0; i < block_size; ++i) {
        vector<unsigned char> transposed_block;
        for (int j = 0; j < blocks.size(); ++j) {
            transposed_block.push_back(blocks[j][i]);
        }
        transposed_blocks.push_back(transposed_block);
    }

    vector<unsigned char> key(block_size);

    for (int i = 0; i < block_size; ++i) {
        key[i] = (unsigned char)find_key(transposed_blocks[i]);
    }

    for (auto& block : blocks) {
        for (int i = 0; i < block.size(); ++i) {
            block[i] ^= key[i % block_size];
        }
    }

    string output;
    for (const auto& block : blocks) {
        output.append(block.begin(), block.end());
    }

    return output;
}

vector<unsigned char> convert_base64_file_to_bytes(const std::string& file_path) {
    // extracting file
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "error: could not open file '" << file_path << "'" << std::endl;
        return {}; // Return an empty vector on error
    }

    std::string text_64, line;
    while (std::getline(file, line)) {
        text_64 += line;
    }
    file.close();

    // base64 to bytes
    static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::vector<unsigned char> decoded_bytes;

    int val = 0, valb = -8;
    for (char c : text_64) {
        if (c == '=') break; 
        val = (val << 6) + base64_chars.find(c);
        valb += 6;

        if (valb >= 0) {
            decoded_bytes.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decoded_bytes;
}

int hamming_distance(const std::vector<unsigned char>& string_byte_1, const std::vector<unsigned char>& string_byte_2) {
  if (string_byte_1.size() != string_byte_2.size()) {
      throw std::invalid_argument("Input vectors must have the same length");
  }

  int distance = 0;
  auto it1 = string_byte_1.begin();
  auto it2 = string_byte_2.begin();

  while (it1 != string_byte_1.end()) {
      unsigned char diff = (*it1) ^ (*it2);
      for (int i = 0; i < 8; ++i) { 
          if (diff & (1 << i)) { 
              distance++;
          }
      }
      ++it1;
      ++it2;
  }

  return distance;
}

vector<unsigned char> string_to_byte_vector(const std::string& str) {
    std::vector<unsigned char> byte_vector;

    for (char c : str) {
        byte_vector.push_back(static_cast<unsigned char>(c));
    }

    return byte_vector;
}
