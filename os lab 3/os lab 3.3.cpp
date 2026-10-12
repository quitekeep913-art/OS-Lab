#include <iostream>
#include <unistd.h>     // fork(), sleep(), getpid()
#include <sys/wait.h>   // wait()

using namespace std;

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child Process
        cout << "Child PID: " << getpid() << " terminating now" << endl;
        exit(0);
    } 
    else if (pid > 0) {
        // Parent Process
        cout << "Parent sleeping for 10s without wait(). Inspect via 'ps -l'" << endl;
        sleep(10); // is doran child zombie rahega
        
        // 10 sec ke baad check karne ke liye dusri terminal me `ps -l` likhna hai
        // to Z+ status dikhega
        
        wait(NULL); // ab child ko clean kiya
        cout << "Parent cleaned up child. Exiting." << endl;
    } 
    else {
        cout << "Fork failed!" << endl;
    }

    return 0;
}