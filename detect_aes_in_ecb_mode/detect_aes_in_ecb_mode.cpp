#include "detect_aes_in_ecb_mode.hpp"

string detect_aes_in_ecb_mode(string file_path) {
    // extracting file
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "it was not possible to open the file" << endl;
    }

    string line;
    int line_number = 1;
    while (getline(file, line)) {
        // break the line into 20 blocks
        unordered_set<string> blocks;
        for (size_t i = 0; i < line.size(); i += 16) {
            string block = line.substr(i, 16);

            // if there are equal blocks that should probably encoded using ecb
            if (blocks.find(block) != blocks.end()) {
                return "line " + to_string(line_number) + " " + line;
            }
            blocks.insert(block);
        }

        line_number++;
    }
    return "no line was encoded using ecb";
}