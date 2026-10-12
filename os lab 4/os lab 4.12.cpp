#include <iostream>
#include <thread>
#include<semaphore>
#include <vector>
#include <chrono>

using namespace std;

// shared semaphore S = permits_available
counting_semaphore<3> sem(3); // 3 permits max

void task(int id) {
    cout << "[Task " << id << "] Waiting for permit..." << endl;

    sem.acquire(); // wait_or_decrement(S) - Blocks if count == 0
    cout << " [Task " << id << "] Acquired! Permits left: doing work..." << endl;

    // perform task
    this_thread::sleep_for(chrono::seconds(2));

    cout << " [Task " << id << "] Done, releasing permit." << endl;
    sem.release(); // increment_or_signal(S)
}

int main() {
    vector<thread> threads;

    for (int i = 1; i <= 10; i++) {
        threads.emplace_back(task, i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    for (auto &t : threads) t.join();

    return 0;
}