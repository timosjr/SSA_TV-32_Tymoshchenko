#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

#define TIMEOUT_MINUTES 0.25

void logout_handler(int signum) {
    const char *msg = "\n[INFO] Auto logout due to inactivity.\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    exit(0);
}

void reset_timer() {
    struct itimerval timer;
    timer.it_value.tv_sec = TIMEOUT_MINUTES * 60;  // час до першого спрацювання
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;  // одноразовий таймер
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}

int main() {
    // Обробник сигналу SIGALRM
    signal(SIGALRM, logout_handler);

    reset_timer();  // Запускаємо таймер

    char input[256];
    while (1) {
        printf("> ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Ctrl+D або помилка
            break;
        }
        reset_timer();  // Скидаємо таймер після кожного введення
        printf("You entered: %s", input);
    }

    return 0;
}
