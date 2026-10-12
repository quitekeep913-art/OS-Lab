#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

atomic<int> counter{0}; // shared atomic_integer counter = 0
const int N = 100000;

void atomic_worker() {
    for (int i = 0; i < N; i++) {
        // hardware_atomic_fetch_and_add(counter, 1)
        counter.fetch_add(1, memory_order_relaxed);
        // OR simply: counter++;
    }
}

int main() {
    thread t1(atomic_worker);
    thread t2(atomic_worker);
    thread t3(atomic_worker);
    thread t4(atomic_worker);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "Expected: " << 4 * N << endl;
    cout << "Actual:   " << counter.load() << " (Lock-free, no race!)" << endl;

    return 0;
}