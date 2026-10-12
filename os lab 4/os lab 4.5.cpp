#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int counter = 0; // shared integer counter = 0
const int N = 100000;

void increment_routine() {
    for (int i = 0; i < N; i++) {
        // This is what counter++ expands to:
        // temp = counter      // Load
        // temp = temp + 1     // Modify
        // counter = temp      // Store (Interleaving here causes loss)
        
        counter++; // Race condition occurs here across concurrent threads
    }
}

int main() {
    thread t1(increment_routine);
    thread t2(increment_routine);

    t1.join();
    t2.join();

    cout << "Expected counter value: " << 2 * N << endl;
    cout << "Actual counter value:   " << counter << endl;
    cout << "Lost updates: " << (2 * N - counter) << endl;

    return 0;
}