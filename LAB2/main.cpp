#include <iostream>
#include <fstream>

const int HEAP_SIZE = 100;
int heap[HEAP_SIZE];
int size = 0;

void makeHeap();
void siftDown(int);

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

    while (fin >> heap[size++]);
    makeHeap();
    
    for (int i = 0; i < 5; i++) {
        std::cout << heap[i] << " " << std::endl;
    }

    fin.close();
    return 0;
}

void makeHeap() {
    int i;
    std::cerr << "In makeHeap " << size << std::endl;

    for (i = size/2; i >= 0; i--) {
        std::cerr << "siftDown " << i << " " << heap[i] << std::endl;
        siftDown(i);
    }
}

void siftDown(int current) {
    int child = 2 * current + 1;
    if (child >= size) { return; }
    if ((child + 1 < size) && (heap[child] < heap[child + 1])) {child++;}
    if (heap[current] < heap[child]) {
        siftDown(child);
        int temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
    }


    return;
}