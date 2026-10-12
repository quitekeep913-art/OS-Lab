#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex M; // shared mutex M
int counter = 0; // shared integer counter = 0
const int N = 100000;

void safe_increment() {
    for (int i = 0; i < N; i++) {
        // acquire_lock(M)
        // RAII lock acquisition inside thread body:
        lock_guard<mutex> lock(M);

        counter = counter + 1; // Critical section

        // release_lock(M) - automatically done when lock_guard goes out of scope
    }
}

int main() {
    thread t1(safe_increment);
    thread t2(safe_increment);
    thread t3(safe_increment);
    thread t4(safe_increment);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "Expected: " << 4 * N << endl;
    cout << "Actual:   " << counter << " (No race condition!)" << endl;

    return 0;
}