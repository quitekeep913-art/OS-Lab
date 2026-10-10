 #include<iostream>
 #include<thread>
 #include<vector>0
 #include<windows.h>
 using namespace std;
  HANDLE sem;
 void worker(int id){
 WaitForSingleObject(sem,INFINITE);
     cout<<"Thread\t"<<id <<" acquiredresource.\n";
     Sleep(1000);
    cout<<"Thread\t"<<id <<" releasing resource.\n";
      ReleaseSemaphore(sem,1, nullptr);
     }
    int main()
	{
     sem=CreateSemaphoreA(nullptr, 2,2,nullptr);
      std::vector<std::thread>threads;
     for(int i= 1; i<=4; ++i){
        threads.emplace_back(worker,i);
   }
      for(auto&t: threads) {
        t.join();
     }
          CloseHandle(sem);
          return 0;
      }