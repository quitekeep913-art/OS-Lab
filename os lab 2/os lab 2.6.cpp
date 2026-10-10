 #include<iostream>
 #include<thread>
 #include<windows.h>
using namespace std;
 void pinnedWorker(){
 //Bitmask:bit0= Core0(value1),bit1 = Core1(value2),etc.
 DWORD_PTR mask=1;
 DWORD_PTR prev=SetThreadAffinityMask(GetCurrentThread(),mask);
 if(prev!=0) {
    cout<<"Thread successfully bound to Core0.\n";
 }
 }

 int main(){
 cout<<"Available hardware cores:"<<std::thread::hardware_concurrency() <<"\n";
 thread t(pinnedWorker);
 t.join();
 return 0;
 }