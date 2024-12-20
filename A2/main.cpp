#include <iostream>
#include <fstream>
// needed to include iomanip for decimal printing
#include <iomanip>

/*
    Ethan Dakin
    SN: 8209194
*/

// Customer struct (record)
struct customer {
    float arrival, service;
    int priority;
};



// Max size of customers in queue
const int MAX_SIZE = 100;

// Queue implementation
class Queue {
    private:
        // Queue array
        customer queue[MAX_SIZE];
        int start, next, size, max_size;
    public:
        // Constructor
        Queue() : start(0), next(0), size(0), max_size(0) {}

        // Enqueue
        void enqueue(customer &c) {
            // If the queue is full, break
            if (isFull()) {
                return;
            }

            // The current position
            int pos = next;
            // Find the position to insert based on priority and arrival time
            for (int i = start; i < next; i++) {
                // If the priority is greater than i's priority, adjust position
                if (c.priority > queue[i].priority || 
                    (c.priority == queue[i].priority && c.arrival < queue[i].arrival)) {
                    pos = i;
                    break;
                }
            }

            // Shift the elements to the right
            for (int i = next; i > pos; i--) {
                queue[i] = queue[i - 1];
            }

            // Insert
            queue[pos] = c;
            // Increase size and next pointer
            next++;
            size++;

            // If the size is greater than max size, adjust accordingly
            if (size > max_size) {
                max_size = size;
            }
        }

        // Dequeue
        customer dequeue() {
            // If the queue is empty then, return an empty customer
            if (isEmpty()) {
                return customer{};
            }
            // Old customer from prior position
            customer old = queue[start];
            // Move start index
            start++;
            // Decrease the size
            size--;
            // Return the old customer
            return old;
        }

        // Is full
        bool isFull() const {
            return size == MAX_SIZE;
        }

        // Get size
        int getSize() const {
            return size;
        }

        // Is empty
        bool isEmpty() const {
            return size == 0;
        }

        // Get max size
        int getMaxSize() const {
            return max_size;
        }
};

class Teller {
    private:
        // Fields for class
        bool busy;
        float idleTime, finishTime, lastFinishTime;
        int servedCustomers;
    public:
        // Constructor
        Teller() : busy(false), idleTime(0), finishTime(0), lastFinishTime(0), servedCustomers(0) {}

        // Is busy
        bool isBusy() const {
            return busy;
        }

        // Serve customer
        void serveCustomer(float currentTime, float serviceTime) {
            if (!busy) {
                // If idle, accumulate idle time from last finish to the current time
                idleTime += currentTime - lastFinishTime;
            }
            // Set busy to true
            busy = true;
            // Increment finish time based on current time + service time
            finishTime = currentTime + serviceTime;
            // Increase served customers
            servedCustomers++;
        }

        // Check if serving is finished
        bool isFinished(float currentTime) const {
            return currentTime >= finishTime;
        }

        // Call finish service when serving is finished, then set busy to false and adjust last finish time.
        void finishService(float currentTime) {
            busy = false;
            lastFinishTime = currentTime;
        }

        // Getters
        float getIdleTime() const {
            return idleTime;
        }

        int getCustomersServed() const {
            return servedCustomers;
        }

        float getFinishTime() const {
            return finishTime;
        }
};

void simulation(int n_servers, char filename[20], std::ifstream &input) {
    // Create queue, tellers, and sentinel customer
    Queue customerQueue;
    Teller tellers[MAX_SIZE];
    customer c;

    // The total elapsed time
    float currentTime = 0;
    // The total waiting time of customers
    float totalWaitTime = 0;
    // The total time customers have been served
    float totalServiceTime = 0;
    // The total amount of customers
    int totalCustomers = 0;
    // The maximum queue length
    int maxQueueLength = 0;
    // The queue length sum
    int queueLengthSum = 0;
    // The time steps
    int timeSteps = 0;

    // Input into sentinel customer
    while (input >> c.arrival >> c.service >> c.priority) {
        // If arrival and service is 0, then break (final entry)
        if (c.arrival == 0 && c.service == 0) {
            break;
        }

        // Set current time to the current arrival time
        currentTime = c.arrival;

        // For each teller
        for (int i = 0; i < n_servers; i++) {
            // IF the teller is busy and the teller is finished
            if (tellers[i].isBusy() && tellers[i].isFinished(currentTime)) {
                // Finish the tellers service
                tellers[i].finishService(currentTime);
                // If the queue is not empty
                if (!customerQueue.isEmpty()) {
                    // Then the teller will serve the first customer in the queue
                    customer nextCustomer = customerQueue.dequeue();
                    tellers[i].serveCustomer(currentTime, nextCustomer.service);
                    // Increment wait time
                    totalWaitTime += currentTime - nextCustomer.arrival;
                }
            }
        }

        // Sentinel customer served boolean
        bool customerServed = false;
        // For each teller
        for (int i = 0; i < n_servers; i++) {
            // If the teller is not busy then
            if (!tellers[i]. ()) {
                // Serve the first  customer in the queue
                tellers[i].serveCustomer(currentTime, c.service);
                customerServed = true;
                // Break the loop
                break;
            }
        }

        // If the customer has not been served then
        if (!customerServed) {
            // Enqueue the customer (this adjusts by priority, etc.)
            customerQueue.enqueue(c);
        }

        // Increment  timesteps, customers and service time
        int currentQueueLength = customerQueue.getSize();
        queueLengthSum += currentQueueLength;
        timeSteps++;
        totalCustomers++;
        totalServiceTime += c.service;
    }

    // While the queue is not empty
    while (!customerQueue.isEmpty()) {
        // Increment current time
        currentTime++;
        // For each teller
        for (int i = 0; i < n_servers; i++) {
            // If the teller is busy and the teller is finished
            if (tellers[i].isBusy() && tellers[i].isFinished(currentTime)) {
                // finish service for teller
                tellers[i].finishService(currentTime);
                // If the customer queue is not empty
                if (!customerQueue.isEmpty()) {
                    // Serve the next customer
                    customer nextCustomer = customerQueue.dequeue();
                    tellers[i].serveCustomer(currentTime, nextCustomer.service);
                    totalWaitTime += currentTime - nextCustomer.arrival;
                }
            }
        }
    }

    //  Average queue length is the ratio of total queueing time and total customers
    float avgQueueLength = totalWaitTime / totalCustomers;

    // Print outputs
    std::cout << "\nSimulation Inputs" << std::endl;
    std::cout << "Number of tellers: " << n_servers << std::endl;
    std::cout << "Name of input file: " << filename << std::endl;

    std::cout << "\n\nSimulation Statistics" << std::endl;
    std::cout << "Customers Served by Each Teller" << std::endl;
    // For each teller
    for (int i = 0; i < n_servers; ++i) {
        // Print how many customers were served
        std::cout << "Teller [" << i << "]: " << tellers[i].getCustomersServed() << std::endl;
    }

    // Set precision
    std::cout << std::fixed << std::setprecision(3);
    // Print total time of simulation
    std::cout << "Total Time of Simulation: " << currentTime << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    // Print the average service time, waiting time and maximum length of the queue
    std::cout << "Average Service Time per Customer: " << totalServiceTime / totalCustomers << std::endl;
    std::cout << "Average Waiting Time per Customer: " << totalWaitTime / totalCustomers << std::endl;
    std::cout << "Maximum Length of the Queue: " << customerQueue.getMaxSize() << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    // Print the average length of the queue
    std::cout << "Average Length of the Queue: " << avgQueueLength << std::endl;

    // Print the idle rate of each teller
    std::cout << "Average Idle Rate of Each Teller" << std::endl;
    std::cout << std::fixed << std::setprecision(7);
    for (int i = 0; i < n_servers; ++i) {
        // idle rate is the idle time divided by the total time
        float idleRate = tellers[i].getIdleTime() / currentTime;
        std::cout << "Teller [" << i << "]: " << idleRate << std::endl;
    }
    // End of program
}


int main() {
    // Initialze filename, input and tellers variables
    char filename[20];
    std::ifstream input;
    int tellers;

    // Get user input for tellers num
    std::cerr << "Please enter the number of tellers: ";
    std::cin >> tellers;

    // Need to have more than 1 tellers
    if (tellers < 1) {
        std::cerr << "Must have 1 or more tellers." << std::endl;
        return -1;
    }

    // Get user input for input file
    std::cerr << "Please enter the name of the input file: ";
    std::cin >> filename;

    input.open(filename);

    // Verify input
    if (!input)
    {
        std::cerr << "Error opening file " << filename << ". Program will exit. " << std::endl;
        return -1;
    }

    // Run simulation
    simulation(tellers, filename, input);
    return 0;
}
