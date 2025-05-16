#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;

    pid = fork();

    if (pid < 0) {
        // Помилка створення процесу
        perror("fork failed");
        return 1;
    }

    printf("pid = %d, process = %s\n", pid, (pid == 0) ? "child" : "parent");

    return 0;
}
