#include "break_repeating_key_xor.hpp"

string break_repeating_key_xor(string file_path) {
    string text = file_to_string(file_path);
    vector<unsigned char> byte_vector = base64_to_bytes(text);

    // find best keysize
    int best_keysize;
    int min_edit_distance;
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

    // break cipher text in of length of the best keysize
    vector<vector<unsigned char>> blocks;
    int block_size = best_keysize;

    for (size_t i = 0; i < byte_vector.size(); i += block_size) {
        
        int current_block_size = std::min(block_size, static_cast<int>(byte_vector.size() - i));
        vector<unsigned char> block(byte_vector.begin() + i, byte_vector.begin() + i + current_block_size); 
        blocks.push_back(block);
    }

    // transposing blocks
    vector<vector<unsigned char>> transposed_blocks;
    for (int i = 0; i < block_size; ++i) {
        vector<unsigned char> transposed_block;
        for (int j = 0; j < blocks.size(); ++j) {
            transposed_block.push_back(blocks[j][i]);
        }
        transposed_blocks.push_back(transposed_block);
    }

    // finding the key
    vector<unsigned char> key(block_size);

    for (int i = 0; i < block_size; ++i) {
        key[i] = (unsigned char)find_key(transposed_blocks[i]);
    }

    for (auto& block : blocks) {
        for (int i = 0; i < block.size(); ++i) {
            block[i] ^= key[i % block_size];
        }
    }

    // returning deciphered text
    string output;
    for (const auto& block : blocks) {
        output.append(block.begin(), block.end());
    }

    return output;
}

vector<unsigned char> base64_to_bytes(string text) {
    static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::vector<unsigned char> decoded_bytes;

    int val = 0, valb = -8;
    for (char c : text) {
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
