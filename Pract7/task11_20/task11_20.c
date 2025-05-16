#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Задаємо відсоток використання CPU (наприклад, 20%)
#define CPU_USAGE_PERCENT 20
#define CYCLE_MS 1000  // повний цикл = 1000 мс

void sleep_ms(int milliseconds) {
    usleep(milliseconds * 1000);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Некоректний PID\n");
        return 1;
    }

    int active_time = CYCLE_MS * CPU_USAGE_PERCENT / 100;
    int sleep_time = CYCLE_MS - active_time;

    printf("🔧 Обмеження CPU процесу %d до %d%%\n", pid, CPU_USAGE_PERCENT);

    while (1) {
        // Дозволити процесу працювати
        kill(pid, SIGCONT);
        sleep_ms(active_time);

        // Зупинити процес
        kill(pid, SIGSTOP);
        sleep_ms(sleep_time);
    }

    return 0;
}
