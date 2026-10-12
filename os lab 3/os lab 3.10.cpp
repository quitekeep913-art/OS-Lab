#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

queue<int> buffer;
const int CAPACITY = 3;

mutex mtx;
condition_variable cv_producer;
condition_variable cv_consumer;

void producer() {
    for (int item = 1; item <= 5; item++) {
        unique_lock<mutex> lock(mtx);
        
        // Wait if buffer is full
        while (buffer.size() == CAPACITY) {
            cv_producer.wait(lock);
        }

        buffer.push(item);
        cout << "Produced: " << item << endl;

        // Notify consumer that an item is available
        cv_consumer.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 5; i++) {
        unique_lock<mutex> lock(mtx);

        // Wait if buffer is empty
        while (buffer.empty()) {
            cv_consumer.wait(lock);
        }

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        // Notify producer that space is available
        cv_producer.notify_one();
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}