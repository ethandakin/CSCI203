#include <iostream>
#include <fstream>

struct teller {
    float idle;
};

struct customer {
    float arrival;
    int priority;
    float key;
};

const int MAX_SIZE = 100;
customer heap[MAX_SIZE];
int ctr = 0;

customer queue[MAX_SIZE];
int start = 0;
int next = 0;

bool compare(customer a, customer b) {
    if (a.priority > b.priority) {
        return false;
    // } else if (a.priority == b.priority) {
    //     if (a.arrival > b.arrival) {
    //         return true;
    //     } else if (a.arrival == b.arrival) {
    //         // this shouldnt happen..
    //         return true;
    //     } else {
    //         return false;
    //     }
    // } else {
    } else {
        return true;
    }
}

void swap(customer &a, customer &b) {
    customer temp = a;
    a = b;
    b = temp;
}

void siftUp(int i) {
    if (i == 1) {
        return;
    }

    int p =  i / 2;

    if (heap[p].arrival > heap[i].arrival) {
        return;
    } else {
        swap(heap[i], heap[p]);
        siftUp(p);
    }
}

void siftDown(int i) {
    int c = 2 * i + 1;
    if (c >= ctr) { return; }
    if ((c + 1 < ctr) && (heap[c].arrival < heap[c + 1].arrival)) {c++;}
    if (heap[i].arrival < heap[c].arrival) {
        swap(heap[i], heap[c]);
        siftDown(c);
    }
}


void add(customer elt) {
    ctr++;
    heap[ctr] = elt;
    siftUp(ctr);
}

customer remove() {
    customer elt = heap[0];
    heap[0] = heap[ctr];
    ctr--;
    siftDown(0);
    return elt;
}

void enqueue(customer elt) {
    queue[next] = elt;
    next++;

    if (next > MAX_SIZE) {
        next = 1;
    }
}

void dequeue(customer elt) {
    if (start == next) {
        // null
    } else {
        elt = queue[start];
    }

    start++;
    if (start > MAX_SIZE) {
        start = 0;
    }
}

void simulation(int teller_n) {
    //teller tellers[teller_n];

    char filename[20];
    std::ifstream input;

    // Prompt user input
    std::cerr << "Please enter the name of the input file: " << std::endl;
    std::cin >> filename;

    // Open file
    input.open(filename);

    float arrival, service;
    int priority;

    while(input >> arrival >> service >> priority) {
        customer c;
        c.arrival = arrival;
        c.priority = priority;

        add(c);

        ctr++;
    }

    for(int i = 1; i < 100; i++) {
        std::cout << heap[i].arrival << std::endl;
    }

}

int main() {
    simulation(1);
    return 0;
}