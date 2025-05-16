#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 10  // кількість випадкових чисел

// функція для випадкового числа в діапазоні [0.0, 1.0]
double rand_0_1() {
    return (double) rand() / RAND_MAX;
}

// функція для випадкового числа в діапазоні [0.0, n]
double rand_0_n(double n) {
    return rand_0_1() * n;
}

int main() {
    double n;

    // ініціалізація генератора випадкових чисел
    srand((unsigned int) time(NULL));

    printf("Генерація %d випадкових чисел у діапазоні [0.0, 1.0]:\n", COUNT);
    for (int i = 0; i < COUNT; ++i) {
        printf("%f\n", rand_0_1());
    }

    printf("\nВведіть верхню межу діапазону (n > 0): ");
    if (scanf("%lf", &n) != 1 || n <= 0) {
        fprintf(stderr, "Некоректне значення.\n");
        return 1;
    }

    printf("Генерація %d випадкових чисел у діапазоні [0.0, %.2f]:\n", COUNT, n);
    for (int i = 0; i < COUNT; ++i) {
        printf("%f\n", rand_0_n(n));
    }

    return 0;
}
