#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxA, mtxB;

void SafeThread(int id) {
    // This locks both mutexes atomically without deadlock
    scoped_lock lock(mtxA, mtxB); // C++17 - deadlock-safe!
    
    cout << "Thread " << id << " acquired both LockA and LockB safely\n";
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "Thread " << id << " releasing\n";
}

int main() {
    thread t1(SafeThread, 1);
    thread t2(SafeThread, 2);

    t1.join();
    t2.join();

    cout << "No deadlock!" << endl;
    return 0;
}