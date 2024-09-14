#include <iostream>
#include <fstream>

using namespace std;

struct hashNode;

struct hashNode {
    int value;
    bool empty;
    hashNode *next;
};

const int hash_size = 100;
int emptyCount = hash_size;
int longest = 0;

hashNode hashTable[100];

void tableInsert(int incoming) {
    int hash = incoming % hash_size;
    
    if (!(hashTable[hash].next)) {

        emptyCount--;
    } else {
        hashTable[hash].next = &chainInsert(incoming, hashTable[hash].next, 1);
    }

}

hashNode chainInsert(int value, hashNode *current, int chainLength) {
    if (!current) {

    } else {
       
    }

    return *current;
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



}