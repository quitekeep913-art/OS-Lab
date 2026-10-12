#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Going to sleep...\n");
    fflush(stdout);
    sleep(3);
    printf("Waking up!\n");
    return 0;
}
