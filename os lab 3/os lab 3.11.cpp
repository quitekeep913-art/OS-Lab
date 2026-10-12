#include <iostream>
#include <thread>
#include<mutex>
#include <shared_mutex>
#include <vector>

using namespace std;

int shared_data = 0;
shared_mutex rw_lock; // Reader-writer lock

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_lock); // Shared lock for reading
    cout << "Reader " << id << " read value: " << shared_data << endl;
    // lock automatically released here
}

void writer(int id, int val) {
    unique_lock<shared_mutex> lock(rw_lock); // Exclusive lock for writing
    shared_data = val;
    cout << "Writer " << id << " updated value to: " << shared_data << endl;
}

int main() {
    vector<thread> threads;

    // Create some writers and readers
    threads.push_back(thread(writer, 1, 100));
    threads.push_back(thread(reader, 1));
    threads.push_back(thread(reader, 2));
    threads.push_back(thread(writer, 2, 200));
    threads.push_back(thread(reader, 3));

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}