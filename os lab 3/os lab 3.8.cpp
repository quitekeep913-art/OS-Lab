#include <iostream>
#include <thread>

using namespace std;

// Shared global counter - race condition will happen here
int counter = 0;

void increment_task() {
    for (int i = 1; i <= 100000; i++) {
        counter = counter + 1;
    }
}

int main() {
    // Spawn two threads
    thread thread1(increment_task);
    thread thread2(increment_task);

    // Wait for both to finish
    thread1.join();
    thread2.join();

    cout << "Expected: 200000 | Actual counter: " << counter << endl;

    return 0;
}