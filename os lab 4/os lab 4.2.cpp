#include <iostream>
#include <thread>

using namespace std;

void worker(int val, int &ref) {
    cout << "[Child Thread] Received val = " << val << ", ref = " << ref << endl;
    val = val + 10;
    ref = ref + 10;
    cout << "[Child Thread] Modified val to = " << val << ", ref to = " << ref << endl;
}

int main() {
    int local_x = 5; // will be passed by value (copy)
    int local_y = 5; // will be passed by explicit reference

    cout << "[Main] Before thread: local_x = " << local_x << ", local_y = " << local_y << endl;

    // pass local_x by value, local_y by explicit reference to new thread
    // std::ref wraps the variable into a reference_wrapper
    thread t(worker, local_x, std::ref(local_y));

    t.join(); // join thread

    cout << "[Main] After thread: local_x = " << local_x << " (unchanged - copy), local_y = " << local_y << " (changed - ref)" << endl;

    return 0;
}