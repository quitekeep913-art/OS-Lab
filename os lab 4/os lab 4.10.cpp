#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

struct Account {
    int id;
    int balance;
    mutex mtx;
    Account(int i, int b) : id(i), balance(b) {}
};

void transfer_funds(Account& A, Account& B, int amount) {
    if (&A == &B) return;

    // atomically_acquire_without_deadlock(A.lock, B.lock)
    // Acquires all mutexes deadlock-free using resource ordering
    scoped_lock lock(A.mtx, B.mtx);

    // execute transaction
    if (A.balance >= amount) {
        A.balance -= amount;
        B.balance += amount;
        cout << "Transferred $" << amount << " from Account " << A.id 
             << " to Account " << B.id 
             << " | Balances: A=" << A.balance << ", B=" << B.balance << endl;
    } else {
        cout << "Failed transfer $" << amount << " from Account " << A.id << " insufficient funds" << endl;
    }
    
    // release both locks - automatic via RAII
}

int main() {
    Account A(1, 1000);
    Account B(2, 1000);

    // Simulate deadlock scenario:
    // Thread1: A -> B
    // Thread2: B -> A
    // With scoped_lock this is safe!

    thread t1([&]{
        for(int i=0; i<5; i++) transfer_funds(A, B, 100);
    });
    thread t2([&]{
        for(int i=0; i<5; i++) transfer_funds(B, A, 150);
    });

    t1.join();
    t2.join();

    cout << "\nFinal Balances: Account A=" << A.balance << " B=" << B.balance 
         << " Total=" << A.balance + B.balance << endl;

    return 0;
}