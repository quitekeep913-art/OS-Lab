#include <iostream>
#include <unistd.h> // for fork(), execvp()
#include <sys/wait.h> // for wait()

using namespace std;

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child Process
        cout << "Child replacing its binary with '/bin/ls'..." << endl;

        // Arguments array for ls -l
        char* args[] = {(char*)"ls", (char*)"-l", NULL};

        execvp(args[0], args);

        // If execvp fails, this line will execute
        cout << "This line never executes if execvp succeeds!" << endl;
        return 1;
    }
    else if (pid > 0) {
        // Parent Process
        wait(NULL);
        cout << "Parent reaped replaced child image" << endl;
    }
    else {
        cout << "Fork failed!" << endl;
    }

    return 0;
}