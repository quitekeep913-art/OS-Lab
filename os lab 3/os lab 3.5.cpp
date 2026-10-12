#include <iostream>
#include <unistd.h>    // for fork()
#include <sys/wait.h>  // for wait()
#include <cstdlib>

using namespace std;

// Global variable - will be copied, not shared
int shared_counter = 100;

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child Process - gets its own copy of shared_counter
        shared_counter = shared_counter + 50;
        cout << "Child sees shared_counter = " << shared_counter << endl;
        exit(0);
    } 
    else if (pid > 0) {
        // Parent Process - waits for child to finish
        wait(NULL);
        cout << "Parent sees shared_counter = " << shared_counter << endl;
    } 
    else {
        cout << "Fork failed!" << endl;
    }

    return 0;
}