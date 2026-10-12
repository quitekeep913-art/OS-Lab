#include <iostream>
#include <unistd.h> // for pipe, fork, read, write, close
#include <sys/wait.h> // for wait
#include <cstring> // for strlen

using namespace std;

int main() {
    int fd[2]; // fd[0] = read end, fd[1] = write end
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        cerr << "Pipe failed" << endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process - Reader
        close(fd[1]); // Close write end

        read(fd[0], buffer, sizeof(buffer));
        cout << "Child read from pipe: " << buffer << endl;

        close(fd[0]);
    } else {
        // Parent process - Writer
        close(fd[0]); // Close read end

        const char* msg = "Hello Child from Kernel Pipe";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);

        wait(NULL); // Wait for child
    }

    return 0;
}