#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// thread_private integer local_txn_id = 0
thread_local int txn_id = 0; // Each thread has its own distinct copy

// thread_local automatically per-thread, no mutex needed!
thread_local int local_counter = 0;

void run(int thread_num) {
    for (int i = 0; i < 3; i++) {
        // local_txn_id = local_txn_id + 1 // Distinct address per thread
        txn_id = txn_id + 1;
        local_counter++;

        cout << "[Thread " << thread_num << "] txn_id=" << txn_id
             << " addr=" << &txn_id
             << " local_counter=" << local_counter << endl;

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    vector<thread> threads;

    for (int i = 1; i <= 4; i++) {
        threads.emplace_back(run, i);
    }

    // Main thread also has its own copy
    run(0);

    for (auto &t : threads) t.join();

    cout << "\n[Main] Final main txn_id=" << txn_id << " addr=" << &txn_id << endl;

    return 0;
}