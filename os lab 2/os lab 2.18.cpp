 #include<iostream>
 #include<thread>
 #include<shared_mutex>
 #include<vector>
using namespace std;
 shared_mutex rw_lock;
 int sharedData=100;

 void reader(int id){
 //Sharedlock:multiplereadersruntogetherinparallel
 shared_lock<std::shared_mutex>lock(rw_lock);
 cout<<"Reader"<<id <<"read value:"<<sharedData<<"\n";
 }

 void writer(int val){
 //Exclusivelock:blocksallreadersandwritersuntilfinished
 unique_lock<std::shared_mutex>lock(rw_lock);
 sharedData=val;
 cout<<"Writer updated value to:"<< sharedData<< "\n";
 }

 int main(){
 thread r1(reader, 1);
  thread r2(reader, 2);
 thread w1(writer, 200);
 thread r3(reader, 3);

 r1.join();r2.join(); w1.join(); r3.join();
 return 0;
 }
