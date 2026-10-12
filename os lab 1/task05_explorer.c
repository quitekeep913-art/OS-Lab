#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* On Linux/Mac use "ls -l". On Windows change this to "dir". */
#ifdef _WIN32
    system("dir");
#else
    system("ls -l");
#endif
    return 0;
}
