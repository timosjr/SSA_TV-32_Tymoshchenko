#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    // Визначення максимального значення time_t
    time_t max_time = (time_t)~((time_t)1 << (sizeof(time_t) * 8 - 1));
    printf("Максимальне значення time_t: %lld\n", (long long)max_time);
    
    // Перетворення в людський формат
    printf("Максимальна дата і час: %s", ctime(&max_time));

    // Визначення розміру time_t
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));

    return 0;
}
