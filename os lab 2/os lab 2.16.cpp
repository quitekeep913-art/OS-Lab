#include <windows.h>
#include <iostream>
using namespace std;

int main(){
    char* page=(char*)VirtualAlloc(nullptr,4096,MEM_COMMIT,PAGE_READWRITE);
    page[0]='A'; // Normal write works fine
    cout << "Write A success, page is READWRITE\n";

    // Downgrade page permission to READ-ONLY at the hardware level
    DWORD oldProtect;
    VirtualProtect(page,4096,PAGE_READONLY,&oldProtect);
    cout << "Page now READ-ONLY\n";

    __try{
        page[0]='B'; // CPU intercepts illegal write!
        cout << "This line will never print\n";
    }
    __except(EXCEPTION_EXECUTE_HANDLER){
        cout<<"Hardware memory protection trap caught!\n";
        cout<<"Access Violation - Cannot write to READ-ONLY page!\n";
    }

    VirtualFree(page,0,MEM_RELEASE);
    return 0;
}