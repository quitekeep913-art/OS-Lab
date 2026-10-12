#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    if (pid == 0) {
        sleep(2);          /* child sleeps for 2 seconds */
    } else {
        wait(NULL);        /* parent waits for the child to finish */
        printf("All done!\n");
    }
    return 0;
}
