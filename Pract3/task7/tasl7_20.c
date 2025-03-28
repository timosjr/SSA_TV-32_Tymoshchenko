#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void run_process() {
    while (1) {
        // Нескінченний цикл для навантаження CPU
    }
}

int main() {
    printf("Testing ulimit -r impact on process priority...\n");
    
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int priority = 0;
            if (setpriority(PRIO_PROCESS, 0, priority) != 0) {
                perror("Failed to set priority");
            }
            printf("Child process %d started with priority %d\n", getpid(), getpriority(PRIO_PROCESS, 0));
            run_process();
        }
    }
    
    sleep(5); // Дати процесам час для виконання
    return 0;
}
