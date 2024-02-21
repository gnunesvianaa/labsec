#include "main.hpp"

int main()
{
    cout << "===== Welcome to Solutions for Cryptopal Challenges =====" << endl;
    cout << endl;

    bool running = true;
    while (running){
        int choice;
        cout << "Enter the number of the chosen challenge (0 for quit): ";
        cin >> choice;
        cout << endl;
        
        switch (choice){
            case 0:
                running =  false;
                break;
            case 1: {
                cout << "Challenge: Convert hex to base64" << endl;

                string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
                cout << "Input: " << input << endl;

                string output = convert_hex_to_base64(input);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            } 
            case 2: {
                cout << "Challenge: Fixed XOR" << endl;

                string input_1 = "1c0111001f010100061a024b53535009181c";
                cout << "Input 1: " << input_1 << endl;
                string input_2 = "686974207468652062756c6c277320657965";
                cout << "Input 2: " << input_2 << endl;

                string output = fixed_xor(input_1, input_2);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 3: {
                cout << "Challenge: Single-byte XOR cipher" << endl;

                string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
                cout << "Input: " << input << endl;

                string output = single_byte_xor_cipher(input);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 4: {
                cout << "Challenge: Detect single-character XOR" << endl;

                string input = "detect_single_character_xor/strings.txt";
                cout << "Input: " << input << endl;

                string output = detect_single_character_xor(input);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 5: {
                cout << "Challenge: Implement repeating-key XOR" << endl;

                string input_1 = "Burning 'em, if you ain't quick and nimbl\r\nI go crazy when I hear a cymbal";
                cout << "Input 1: " << input_1 << endl;
                string input_2 = "ICE";
                cout << "Input 2: " << input_2 << endl;

                string output = implement_repeating_key_xor(input_1, input_2);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 6: {
                cout << "Challenge: Break repeating-key XOR" << endl;

                string input = "break_repeating_key_xor/encripted64.txt";
                cout << "Input: " << input << endl;

                string output  = break_repeating_key_xor(input);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 7: {
                cout << "Challenge: AES in ECB mode" << endl;

                string input_1 = "aes_in_ecb_mode/encoded_base64.txt";
                cout << "Input 1: " << input_1 << endl;

                string input_2 = "YELLOW SUBMARINE";
                cout << "Input 2: " << input_2 << endl;

                string output  = aes_in_ecb_mode(input_1, input_2);
                cout << "Output: " << output << endl;
                cout << endl;

                break;
            }
            case 8: {
                cout << "Challenge: Detect AES in ECB mode" << endl;

                string input = "detect_aes_in_ecb_mode/encoded_hex.txt";
                cout << "Input: " << input << endl;

                string output = detect_aes_in_ecb_mode(input);
                cout << "Output: " << output << endl;
                cout << endl;
                
                break;
            }
            default:
                cout << "Challenge not found" << endl;
                cout << endl;
        }

    }
}