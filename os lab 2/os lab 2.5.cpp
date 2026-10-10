 #include<iostream>
 #include<windows.h>
 using namespace std;
 int main(){
 //Step1:Reserve1 MBofvirtualaddresses(noRAMallocatedyet)
 void*base=VirtualAlloc(nullptr,1024*1024,
 MEM_RESERVE,PAGE_NOACCESS);
 if(!base) return 1;
 cout<<"Reserved 1MB address space at:" <<base<<"\n";

 //Step2:Back the first4KBpagewithactualphysicalRAM
 int*page=(int*)VirtualAlloc(base, 4096,
 MEM_COMMIT, PAGE_READWRITE);
 if(!page) return 1;

 page[0]=42;//Now safetoreadandwrite
 cout<<"Committed memory value:"<<page[0]<<"\n";

 VirtualFree(base, 0,MEM_RELEASE);// Clean upbothatonce
 return 0;
 }