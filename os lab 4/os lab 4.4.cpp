#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void worker_fn() {
    cout << "[Worker jthread " << this_thread::get_id() << "] Started working..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "[Worker jthread " << this_thread::get_id() << "] Finished working." << endl;
}

int main() {
    cout << "[Main] Main thread ID: " << this_thread::get_id() << endl;

    {
        cout << "[Main] Begin scope" << endl;

        // create joinable_auto_thread(worker_fn)
        jthread jt(worker_fn); // Automatically issues join() on destruction

        cout << "[Main] jthread created, doing main work in scope..." << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "[Main] Scope ending, jt destructor will call join() automatically" << endl;
        // On scope exit, destructor calls join() automatically
    } // <-- jt.join() called here automatically

    cout << "[Main] Scope exited, worker guaranteed finished. Main continues." << endl;

    return 0;
}