#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("UID = %d\n", getuid());
    printf("EUID = %d\n", geteuid());
    printf("USER = %s\n", getenv("USER"));
    printf("HOME = %s\n", getenv("HOME"));
    printf("LOGNAME = %s\n", getenv("LOGNAME"));

    return 0;
}
