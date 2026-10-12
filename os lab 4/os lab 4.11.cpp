#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;
bool finished = false;

void Producer() {
    for (int i = 1; i <= 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(200));

        {
            lock_guard<mutex> lock(mtx); // lock(mutex)
            q.push(i); // push item into queue
            cout << "[Producer] Produced: " << i << endl;
        }

        cv.notify_one(); // notify_one(cond_var)
        // unlock(mutex) -> auto via lock_guard
    }

    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();
}

void Consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx); // lock(mutex)

        // while queue is empty:
        // cond_var.wait(mutex) // Releases mutex and puts thread to sleep
        cv.wait(lock, [] { return!q.empty() || finished; });

        if (q.empty() && finished) break;

        int item = q.front(); // pop item from queue
        q.pop();

        lock.unlock(); // unlock(mutex) early to allow producing

        cout << " [Consumer " << id << "] Consumed: " << item << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread prod(Producer);
    thread cons1(Consumer, 1);
    thread cons2(Consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();

    return 0;
}