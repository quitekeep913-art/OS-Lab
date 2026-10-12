#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Shared global variables
int counter = 0;
mutex mtx; // Create mutex

void safe_increment() {
    for (int i = 1; i <= 100000; i++) {
        mtx.lock();
        counter = counter + 1;
        mtx.unlock();
    }
}

int main() {
    // Spawn two threads
    thread thread1(safe_increment);
    thread thread2(safe_increment);

    // Wait for both to finish
    thread1.join();
    thread2.join();

    cout << "Final counter with Mutex: " << counter << endl;

    return 0;
}