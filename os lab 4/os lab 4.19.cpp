#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

const int N = 5;
vector<mutex> forks(N);

void dine(int philosopher_id) {
    int left = philosopher_id;
    int right = (philosopher_id + 1) % N;

    // function dine(philosopher_id):
    // fork1 = min(left_fork_id, right_fork_id)
    // fork2 = max(left_fork_id, right_fork_id)
    // acquire(fork1) // Always acquire lower-index resource first
    // acquire(fork2)

    int first = min(left, right);
    int second = max(left, right);

    for (int i = 0; i < 3; i++) { // eat 3 times
        cout << "[P" << philosopher_id << "] thinking...\n";
        this_thread::sleep_for(chrono::milliseconds(200 + rand()%300));

        cout << "[P" << philosopher_id << "] hungry, trying forks " << first << " and " << second << endl;

        // Enforce lock acquisition order based on resource IDs:
        unique_lock<mutex> l1(forks[first]);
        cout << "[P" << philosopher_id << "] picked up fork " << first << endl;
        this_thread::sleep_for(chrono::milliseconds(50)); // increase chance of deadlock if ordered wrong

        unique_lock<mutex> l2(forks[second]);
        cout << "[P" << philosopher_id << "] picked up fork " << second << " -> EATING\n";

        // eat()
        this_thread::sleep_for(chrono::milliseconds(300));

        // release(fork2)
        // release(fork1) - unique_lock releases in reverse order automatically
        cout << "[P" << philosopher_id << "] finished eating, released forks\n";
    }
}

int main() {
    vector<jthread> philosophers;
    for (int i = 0; i < N; i++) {
        philosophers.emplace_back(dine, i);
    }
    // jthread auto joins

    return 0;
}