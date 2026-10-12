#include <stdio.h>

int main(void) {
    FILE *f = fopen("ghost.txt", "r");
    if (f == NULL) {
        perror("Failed to open file");
        return 1;
    }
    fclose(f);
    return 0;
}
