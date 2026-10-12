 #include<iostream>
 #include<thread>
 #include<vector>
using namespace std;
 //EachthreadreceivesitsowncompletelyindependentcopyoflocalVal
 thread_local int localVal=0;

 void run(int offset){
localVal+=offset;//ModifiesonlyTHISthread’sprivatecopy
 cout<<"Thread ID:"<< std::this_thread::get_id()
 <<"|local Val=" <<localVal <<"\n";
 }

 int main(){
 thread t1(run,10);
 thread t2(run,20);
 thread t3(run,30);

 t1.join();
 t2.join();
 t3.join();
 return 0;
}