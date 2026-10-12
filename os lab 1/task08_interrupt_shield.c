#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_custom_ignore_function(int sig) {
    (void)sig;
    /* write() is safe to call inside a signal handler, printf is not */
    const char msg[] = "\n You can't close me!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void) {
    signal(SIGINT, my_custom_ignore_function);
    while (1) {
        printf("Running...\n");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
