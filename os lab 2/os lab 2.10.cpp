 #include<iostream>
#include<thread>
 #include<mutex>
 #include<chrono>
using namespace std;
 mutex m1,m2;

 void threadA(){
 m1.lock();
 cout<<"Thread A locked Mutex1,waiting for Mutex 2...\n";
 this_thread::sleep_for(std::chrono::milliseconds(50));
 m2.lock();//BlockswaitingforthreadBtounlockm2
 m2.unlock();
 m1.unlock();
 }

 void threadB(){
 m2.lock();
 cout<<"Thread Blocked Mutex2,waiting for Mutex 1...\n";
 this_thread::sleep_for(std::chrono::milliseconds(50));
 m1.lock();//BlockswaitingforthreadAtounlockm1
 m1.unlock();
 m2.unlock();
 }

 int main(){
 thread t1(threadA);
 thread t2(threadB);
 t1.join();
  t2.join();
 return 0;
 }