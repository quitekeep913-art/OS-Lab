#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int heavy_calc(int n) {
    cout << "[Async Task] Starting heavy computation for n=" << n << endl;
    long long sum = 0;
    for (int i = 0; i < 200000000; i++) sum += i % n;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "[Async Task] Finished" << endl;
    return sum % 1000;
}

int main() {
    cout << "[Main] Scheduling async task..." << endl;

    // handle = schedule_async(heavy_computation_function)
    future<int> fut = async(launch::async, heavy_calc, 10);

    // continue concurrent work in main()
    cout << "[Main] Task scheduled, doing other work in main..." << endl;
    for (int i = 0; i < 3; i++) {
        cout << "[Main] Working... " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "[Main] Now need result, blocking..." << endl;

    // final_result = block_on_handle(handle)
    int res = fut.get(); // blocks until done

    cout << "[Main] Final result = " << res << endl;

    return 0;
}