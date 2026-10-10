 #include<iostream>
 #include<thread>
 #include<mutex>
 #include<condition_variable>
 #include<chrono>
using namespace std;
 condition_variable cv;
 mutex m;
 bool ready=false;

 void consumer(){
 unique_lock<std::mutex>lock(m);
 //Automaticallyunlocksmutexandsleepsuntilproducernotifies
 cv.wait(lock,[]{return ready;});
 cout<<"Conditionmet,consumer awakened.\n";
 }

 void producer(){
 this_thread::sleep_for(std::chrono::milliseconds(500));
 {
lock_guard<std::mutex>lock(m);
 ready=true;
 }
 cv.notify_one(); //Wakeupthesleepingconsumerthread
 }

 int main(){
 thread tCons(consumer);
 thread tProd(producer);
 tCons.join();
 tProd.join();
 return 0;
}