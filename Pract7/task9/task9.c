#include <stdio.h>
#include <sys/time.h>

long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000;
}

int main() {
    long start_time = get_current_time_ms();

    //Фрагмент коду для вимірювання
    for (volatile long i = 0; i < 100000000; i++);

    long end_time = get_current_time_ms();

    printf("Час виконання: %ld мс\n", end_time - start_time);
    return 0;
}
