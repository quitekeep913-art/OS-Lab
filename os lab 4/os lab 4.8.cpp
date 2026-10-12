#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <chrono>

using namespace std;

shared_mutex rw_mtx; // RW_Lock
int shared_data = 0;

void reader(int id) {
    // acquire_shared_access(RW_Lock)
    shared_lock<shared_mutex> r_lock(rw_mtx); // Reader thread

    cout << "[Reader " << id << "] reading data = " << shared_data 
         << " | Thread " << this_thread::get_id() << endl;
    
    this_thread::sleep_for(chrono::milliseconds(500)); // simulate read

    // release_shared_access(RW_Lock) -> auto on destruction
}

void writer(int id) {
    // acquire_exclusive_access(RW_Lock)
    unique_lock<shared_mutex> w_lock(rw_mtx); // Writer thread

    shared_data++;
    cout << "[Writer " << id << "] modified data to = " << shared_data 
         << " | Thread " << this_thread::get_id() << endl;

    this_thread::sleep_for(chrono::milliseconds(500)); // simulate write

    // release_exclusive_access(RW_Lock) -> auto
}

int main() {
    vector<thread> threads;

    // 2 writers and 5 readers
    threads.emplace_back(writer, 1);
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);
    threads.emplace_back(reader, 3);
    threads.emplace_back(writer, 2);
    threads.emplace_back(reader, 4);

    for (auto &t : threads) t.join();

    cout << "Final data = " << shared_data << endl;
    return 0;
}