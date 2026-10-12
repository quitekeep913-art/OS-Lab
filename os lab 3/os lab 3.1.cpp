#include <iostream>
#include <unistd.h>  
#include <sys/types.h>

using namespace std;

int main() {
    int pid = fork(); 

    if (pid < 0) {
        cout << "Process creation failed" << endl;
    } 
    else if (pid == 0) {
        
        cout << "Child Process: PID = " << getpid() << ", Parent PID = " << getppid() << endl;
    } 
    else {
        
        cout << "Parent Process: PID = " << getpid() << ", Created Child PID = " << pid << endl;
    }

    return 0;
}