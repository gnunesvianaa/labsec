#include "calcule_char_categories.hpp"

map<string, int> calculate_char_categories(const string& text) {
    map<string, int> char_categories = {{"lower", 0}, {"upper", 0}, {"space", 0},{"punct", 0}, {"digit", 0}, {"unprint", 0},{"cntrl", 0}, {"other", 0}};

    for (unsigned char c : text) {
        if (islower(c)) {
            char_categories["lower"]++;
        } else if (isspace(c)) {
            char_categories["space"]++;
        } else if (isupper(c)) {
            char_categories["upper"]++;
        } else if (ispunct(c)) {
            char_categories["punct"]++;
        } else if (isdigit(c)) {
            char_categories["digit"]++;
        } else if (iscntrl(c)){
            char_categories["cntrl"]++;
        } else if (!isprint(c)) {
            char_categories["unprint"]++;
        } else {
            char_categories["other"]++;
        }
    }

    return char_categories;
}