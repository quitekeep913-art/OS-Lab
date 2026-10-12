#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Worker(stop_token stoken) {
    cout << "[Worker] Started\n";

    // Worker:
    // while not stop_requested():
    while (!stoken.stop_requested()) {
        cout << "[Worker] do_work()...\n";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "[Worker] Stop requested! cleanup_resources()..." << endl;
    this_thread::sleep_for(chrono::milliseconds(300)); // cleanup
    cout << "[Worker] Cleaned up, exiting" << endl;
}

int main() {
    // jthread auto-joins and has stop_token built-in
    jthread my_jthread(Worker);

    this_thread::sleep_for(chrono::seconds(2));

    cout << "[Manager] send_stop_signal_to_worker()" << endl;

    // From controlling thread:
    my_jthread.request_stop(); // send_stop_signal_to_worker()

    // jthread destructor will join automatically here
    cout << "[Manager] Waiting for worker to finish..." << endl;

    return 0;
}