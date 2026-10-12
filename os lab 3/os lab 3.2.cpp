#include <iostream>
#include <unistd.h>     // fork(), sleep()
#include <sys/wait.h>   // wait()
#include <cstdlib>      // exit()

using namespace std;

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child Process
        cout << "Child executing task..." << endl;
        sleep(2); // 2 second wait
        cout << "Child exiting with code 42" << endl;
        exit(42);
    } 
    else if (pid > 0) {
        // Parent Process
        cout << "Parent waiting for child..." << endl;
        int status = 0;
        wait(&status); // child ka wait
        
        int exit_code = WEXITSTATUS(status); // EXTRACT_EXIT_CODE ka sahi function ye hai
        
        cout << "Parent: Child terminated with exit status " << exit_code << endl;
    } 
    else {
        cout << "Fork failed!" << endl;
    }

    return 0;
}