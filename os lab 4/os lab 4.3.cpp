#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void logger() {
    while (true) {
        // flush_buffer_to_disk()
        cout << "[Logger Thread " << this_thread::get_id() << "] Flushing buffer to disk..." << endl;

        // sleep(5 seconds)
        this_thread::sleep_for(chrono::seconds(5));
    }
}

int main() {
    cout << "[Main] Main thread ID: " << this_thread::get_id() << endl;

    // spawn logger thread
    thread t(logger);

    // detach thread from parent handle
    t.detach(); // OS manages PCB/TCB deallocation upon thread termination

    cout << "[Main] Logger detached. Main continues and will exit in 12 seconds..." << endl;

    // Main does its own work
    for (int i = 1; i <= 3; i++) {
        cout << "[Main] Doing main work " << i << endl;
        this_thread::sleep_for(chrono::seconds(4));
    }

    cout << "[Main] Main exiting. Detached logger will be terminated by OS." << endl;
    return 0;
}