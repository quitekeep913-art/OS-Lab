#include <stdio.h>

int main(void) {
    FILE *file = fopen("diary.txt", "w");
    if (file == NULL) {
        perror("Could not create diary.txt");
        return 1;
    }
    fprintf(file, "Hello OS\n");
    fclose(file);
    return 0;
}
