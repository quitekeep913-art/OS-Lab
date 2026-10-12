#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mutexA;
mutex mutexB;

void thread1_work() {
    cout << "Thread 1: Locking mutexA" << endl;
    mutexA.lock();
    this_thread::sleep_for(chrono::seconds(1)); // Hold mutexA and wait
    
    cout << "Thread 1: Trying to lock mutexB" << endl;
    mutexB.lock(); // Will wait forever if Thread2 holds mutexB
    
    cout << "Thread 1: Got both locks" << endl;
    mutexB.unlock();
    mutexA.unlock();
}

void thread2_work() {
    cout << "Thread 2: Locking mutexB" << endl;
    mutexB.lock();
    this_thread::sleep_for(chrono::seconds(1)); // Hold mutexB and wait

    cout << "Thread 2: Trying to lock mutexA" << endl;
    mutexA.lock(); // Will wait forever if Thread1 holds mutexA

    cout << "Thread 2: Got both locks" << endl;
    mutexA.unlock();
    mutexB.unlock();
}

int main() {
    thread t1(thread1_work);
    thread t2(thread2_work);

    t1.join();
    t2.join();

    cout << "Finished - This will never print if deadlock happens" << endl;
    return 0;
}