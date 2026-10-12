#include<iostream>
#include<windows.h>
using namespace std;
int main(){
 HANDLE hFile=CreateFileA("async.bin", GENERIC_WRITE,0,nullptr,
 CREATE_ALWAYS, FILE_FLAG_OVERLAPPED,nullptr);
 if(hFile==INVALID_HANDLE_VALUE) return 1;

 OVERLAPPED ol{};
 ol.hEvent=CreateEventA(nullptr,TRUE, FALSE, nullptr);
 char buffer[1024]="Asynchronous file write data packet.";

 //Non-blockingwrite:immediatelyhandscontrolbacktoCPU
 WriteFile(hFile, buffer, sizeof(buffer),nullptr,&ol);
 cout<<"I/Oinitiated.Doing computation in parallel...\n";

 //Waitonlywhenwe actually require confirmationfromdisk
 WaitForSingleObject(ol.hEvent,INFINITE);
 cout<<"Asynchronous write fully committed.\n";

 CloseHandle(ol.hEvent);
 CloseHandle(hFile);
  return 0;
 }