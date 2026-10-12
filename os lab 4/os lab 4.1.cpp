#include <iostream>
#include <thread>

using namespace std;

// child_routine function
void child_routine() {
    cout << "Child executing with unique thread ID: " 
         << this_thread::get_id() << endl;
}

int main() {
    cout << "Main thread ID: " << this_thread::get_id() << endl;

    // spawn child_thread running child_routine
    thread child_thread(child_routine);

    cout << "Main waiting for child to finish..." << endl;

    // wait_for_thread_to_finish(child_thread)
    child_thread.join(); // Blocks calling thread until 't' finishes

    cout << "Child finished. Main thread resuming." << endl;

    return 0;
}