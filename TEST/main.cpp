#include <iostream>
#include <fstream>

struct customer {
    float arrival;
    float departure;
    int priority;
};

const int MAX_SIZE = 100;

// queue of null pointers
customer *queue[MAX_SIZE - 1] = {};
int start = 0;
int next = 0;

void enqueue(customer elt) {
    queue[next] = &elt;
    next++;

    if (next > (MAX_SIZE - 1)) {
        next = 0;
    }
}

void dequeue(customer elt) {
    if (start != next) {
        elt = *queue[start];
    }

    start++;
    if (start > (MAX_SIZE - 1)) {
        start = 0;
    }
}

int main() {
    customer Test;
    Test.arrival = 0.1;
    Test.departure = 0.2;
    Test.priority = 3;
    enqueue(Test);

    for (int i = 0; i < MAX_SIZE; i++) {
        std::cout << queue[i]->arrival << std::endl;
    }

    return 0;
}