#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        printf("Hello, %s!\n", argv[i]);
    }
    return 0;
}
