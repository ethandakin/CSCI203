#include <iostream>
#include <fstream>
#include <string.h>

const int SIZE = 50000;
const int WORD_SIZE = 10;

char text[SIZE * WORD_SIZE];
int start[SIZE];

bool is_whitespace(char c) {
    if ((c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')) {
        return true;
    } else {
        return false;
    }
}

bool is_alphabet(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
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

    int index = 0;
    int word = 0;
    int cindex = 0;

    char c;
    bool toggle = false;


    while (fin.get(c)) {
        if (is_whitespace(c)) {
            // go ot next in start array
            if (!toggle) {
                word++;
                toggle = true;
                cindex = 0;
            }

        } else if (is_alphabet(c)) {
            // write in char array
            if (toggle) {
                toggle = false;
            }

            if (cindex == 0) {
                start[word] = index;
            }

            text[index] = lower(c);
            index++;
            cindex++;
        }
    }

    for (int i = 0; i < word; i++) {

        for (int k = start[i]; k < start[i + 1]; k++) {
            std::cout << text[k];
        }

        std::cout << std::endl;

        //std::cout << start[i] << " : " << start[i + 1] - 1 << std::endl;
        //std::cout << text[start[i]] << text[start[i + 1] - 1] << std::endl;

    }

    return 0;
} 