#include <iostream>
#include <thread>
#include <latch>
#include <vector>
#include <chrono>

using namespace std;

void worker(int id, latch& start_flag, latch& done_flag) {
    cout << "[Worker " << id << "] Ready, waiting for start signal..." << endl;

    start_flag.wait(); // wait_for_latch_zero(L)

    // All workers start exactly at same time here
    cout << "[Worker " << id << "] GO! Running benchmarks..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500 + id * 100)); // run_benchmarks()
    cout << "[Worker " << id << "] Finished" << endl;

    done_flag.count_down();
}

int main() {
    const int num_workers = 5;

    latch start_flag(1); // shared latch L initialized to 1
    latch done_flag(num_workers); // to wait for all workers to finish

    vector<jthread> workers;
    for (int i = 1; i <= num_workers; i++) {
        workers.emplace_back(worker, i, ref(start_flag), ref(done_flag));
    }

    cout << "[Main] Preparing shared memory..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // prepare_shared_memory()
    cout << "[Main] Preparation done." << endl;

    cout << "[Main] Releasing all workers NOW!" << endl;
    start_flag.count_down(); // decrement_latch(L) // Triggers simultaneous worker release

    done_flag.wait(); // wait for all workers
    cout << "[Main] All workers finished. Benchmark complete." << endl;

    return 0;
}