#include <iostream>
#include <fstream>

const int SIZE = 50000;
const int WORD_SIZE = 50;

char words[SIZE][WORD_SIZE];

const char punctuation[11] = {};
const char whitespace[6] = {};

bool is_whitespace(char c) {
    if ((c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')) {
        return true;
    } else {
        return false;
    }
}

bool is_punctuation(char c) {
    if (c == ',' || c == '.' || c ==  '(' || c ==  ')' || c ==  '-' || c ==  ':' || c ==  '?' || c ==  '\'' || c ==  ';' || c ==  '!' || c == '"') {
        return true;
    } else {
        return false;
    }
}

//ascii lower hack
char lower(char c) {
    if (c <= 'Z' && c >= 'A') {
        return c + 32;
    }

    return c;
}

int main() {
    char filename[20];
    std::ifstream fin;

    std::cerr << "Please enter the name of the input file: ";
    std::cin >> filename;

    fin.open(filename);

    if (!fin) {
        std::cerr << "Error opening file " << filename << ". Program will exit. " << std::endl;
        return 0;
    }

    char c;

    int index = 0;
    int start = 0;

    while (fin.get(c)) {
        if (is_punctuation(c)) {
            continue;
        }

        if (is_whitespace(c)) {
            if (start != -1) {
                index++;
                start = -1;
            }
        } else {
            if (start == -1) {
                start = 0;
            }

            //std::cout << index << std::endl;
            words[index][start] = lower(c);
            start++;
        }
    }

    for (int i = 0; i < index; i++) {
        std::cout << words[i] << std::endl;
    }




    return 0;
}