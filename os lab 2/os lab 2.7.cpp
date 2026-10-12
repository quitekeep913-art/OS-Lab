 #include<iostream>
 #include<future>
 #include<chrono>
 #include<thread>
using namespace std;
 int main(){
 //Dispatchworktorunin thebackground
   future<double>task =std::async(std::launch::async,[](){
    this_thread::sleep_for(std::chrono::seconds(1));
 return 3.14159;
 });

   cout<<"Main thread continues work while async task computes...\n";

 //.get()pausesexecutiononlyuntiltheresultis ready
 double result=task.get();
   cout<<"Result received:"<<result<<"\n";
 return 0;
 }
