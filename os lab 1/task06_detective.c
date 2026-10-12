#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Linux/Mac use USER, Windows uses USERNAME */
    const char *user = getenv("USER");
    if (user == NULL) user = getenv("USERNAME");
    if (user == NULL) user = getenv("LOGNAME");
    if (user == NULL) user = "(unknown)";
    printf("Current user is: %s\n", user);
    return 0;
}
