#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

class ThreadPool {
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mtx;
    condition_variable cv;
    bool stop = false;

public:
    ThreadPool(int num_threads) {
        for (int i = 0; i < num_threads; i++) {
            workers.emplace_back([this, i] {
                // Worker Loop (Fixed Pool):
                while (true) {
                    function<void()> task;

                    { // lock task_queue
                        unique_lock<mutex> lock(queue_mtx);

                        // wait until queue not empty OR shutdown
                        cv.wait(lock, [&] { return stop ||!tasks.empty(); });

                        if (stop && tasks.empty()) return;

                        // task = dequeue()
                        task = move(tasks.front());
                        tasks.pop();
                    } // unlock task_queue

                    // execute(task) outside lock!
                    // cout << "[Worker " << i << "] executing\n";
                    task();
                }
            });
        }
    }

    void enqueue(function<void()> task) {
        {
            lock_guard<mutex> lock(queue_mtx);
            tasks.push(move(task));
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            lock_guard<mutex> lock(queue_mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto &w : workers) w.join();
    }
};

void heavy_work(int id) {
    cout << "[Task " << id << "] on thread " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ThreadPool pool(4); // 4 worker threads

    for (int i = 1; i <= 10; i++) {
        pool.enqueue([i]{ heavy_work(i); });
    }

    this_thread::sleep_for(chrono::seconds(3));
    cout << "Main done, pool destructor will wait for tasks\n";
    return 0;
}