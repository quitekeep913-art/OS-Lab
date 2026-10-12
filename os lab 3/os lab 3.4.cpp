#include <iostream>
#include <unistd.h>   // for fork(), sleep(), getpid(), getppid()
#include <cstdlib>    // for exit()

using namespace std;

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child Process
        cout << "Initial Parent PID: " << getppid() << endl;
        sleep(3); // Wait for parent to terminate
        cout << "After parent dies, new Parent PID: " << getppid() << endl;
        exit(0);
    } 
    else if (pid > 0) {
        // Parent Process
        cout << "Parent PID: " << getpid() << " exiting immediately" << endl;
        exit(0); // Parent exits immediately, child becomes orphan
    } 
    else {
        // Fork failed
        cout << "Fork failed!" << endl;
    }

    return 0;
}