#include "aes_in_ecb_mode.hpp"

std::string aes_in_ecb_mode(std::string file_path, std::string key_string) {
    string text_64 = file_to_string(file_path);

    string text = base64_decode(text_64);

    // initialize OpenSSL
    OpenSSL_add_all_algorithms();

    // get the desired cipher
    const EVP_CIPHER *cipher = EVP_aes_128_ecb();

    // create a decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!EVP_DecryptInit_ex(ctx, cipher, nullptr, nullptr, nullptr)) {
        std::cerr << "Error: it was not possible to create a decryption context" << std::endl;
        return {};
    }

    // set the key
    if (key_string.size() != 16) {
        std::cerr << "Error: Key must be exactly 16 bytes for AES-128!" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    unsigned char key[16];
    std::copy(key_string.begin(), key_string.end(), key); 
    
    if (!EVP_DecryptInit_ex(ctx, nullptr, nullptr, key, nullptr)) {
        std::cerr << "Error: it was not possible to set the decryption key" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    int plaintext_len, len;

    // allocate buffer for decrypted plaintext
    std::vector<unsigned char> plaintext(text.size() + EVP_MAX_BLOCK_LENGTH); // Allocate extra space for potential padding

    // decrypt the ciphertext
    if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, (const unsigned char*)text.c_str(), text.size())) {
        std::cerr << "Error: it was not possible to decrypt" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    plaintext_len = len;

    // finalize the decryption
    if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        std::cerr << "Error: couldn't finalize decryption" << std::endl;
        return {};
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx); 

    // return the decrypted plaintext
    return std::string(plaintext.begin(), plaintext.begin() + plaintext_len);
}


std::string base64_decode(const std::string &input) {
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string output;
    std::vector<int> decoded_values(input.size());
    int i = 0;

    for (char c : input) {
        decoded_values[i++] = base64_chars.find(c);
    }

    i = 0;
    while (i < decoded_values.size()) {
        // process groups of 4 encoded characters to extract 3 bytes
        output += (decoded_values[i] << 2) | (decoded_values[i + 1] >> 4);
        if (i + 2 < decoded_values.size()) { 
             output += (decoded_values[i + 1] << 4) | (decoded_values[i + 2] >> 2);
        }
        if (i + 3 < decoded_values.size()) {
            output += (decoded_values[i + 2] << 6) | decoded_values[i + 3];
        }
        i += 4;
    }
    return output;
}