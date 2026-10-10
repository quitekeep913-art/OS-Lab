 #include<iostream>
 #include<windows.h>
using namespace std;
 int main(){
 int x= 10; //Variableallocated onthestack
 MEMORY_BASIC_INFORMATION mbi{};

 //Askthekernelfor metadataabout the pageholdingvariable x
 if(VirtualQuery(&x,&mbi,sizeof(mbi)) != 0){
  cout<<"Address: "<<mbi.BaseAddress<<"\n";
  cout<<"RegionSize:"<<mbi.RegionSize<<" bytes\n";
    cout<<"State: "<<(mbi.State ==MEM_COMMIT ? "MEM_COMMIT" :"OTHER")
 <<"\n";
 }
 return 0;
 }
