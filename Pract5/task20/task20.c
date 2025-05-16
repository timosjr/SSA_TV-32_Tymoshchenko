#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        size_t size = 4096;
        void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        if (mem == MAP_FAILED) {
            perror("mmap failed");
            exit(EXIT_FAILURE);
        }

        strcpy((char *)mem, "Це пам'ять, яку ми втратимо після fork().");
        printf("Дочірній процес: %s\n", (char *)mem);
        _exit(0);
    } else {
        wait(NULL);
        printf("Батьківський процес завершився без витоків пам'яті.\n");
    }

    return 0;
}
