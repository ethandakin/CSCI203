#include <iostream>
#include <fstream>
using namespace std;

const int STACK_SIZE = 100;
const int WORD_SIZE = 20;
char stack[STACK_SIZE][WORD_SIZE];
int top = 0;

void push(char word[]) {
    if (top == STACK_SIZE) {
        return;
    }

    int i = 0;

    do {
        stack[top][i] = word[i];
        i++;
    } while (word[i]);
    top++;
    return;
}

char *pop() {
    return stack[--top];
}

bool isEmpty() {
    return top == 0;
}

int main() {
    char filename[20];
    ifstream fin;
    
    cerr << "Please enter the name of the input file: ";
    cin >> filename;
    fin.open(filename);

    if (!fin) {
        cerr << "Error opening file " << filename << ". Program will exit." << endl;
        return 0;
    }

    char word[WORD_SIZE];

    while (fin >> word) {
        push(word);
    }

    while (!isEmpty()) {cout << pop() << endl;}

    fin.close();

    return 0;
}