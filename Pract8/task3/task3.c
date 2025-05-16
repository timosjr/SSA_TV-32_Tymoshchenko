#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ARRAY_SIZE 10000

// Функція порівняння для цілих чисел
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

// Перевірка, чи масив відсортований
bool is_sorted(int *arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Створення масиву з випадковими значеннями
void generate_random_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        arr[i] = rand() % 10000;
    }
}

// Створення масиву, відсортованого у зворотному порядку (часто поганий випадок для поганих реалізацій quicksort)
void generate_reverse_sorted_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        arr[i] = (int)(n - i);
    }
}

// Створення масиву, де всі значення однакові
void generate_equal_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        arr[i] = 42;
    }
}

// Вимірювання часу виконання qsort
double time_qsort(int *arr, size_t n) {
    clock_t start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand((unsigned int)time(NULL));

    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }

    printf("Тестуємо qsort з різними масивами (%d елементів):\n", ARRAY_SIZE);

    // Випадковий масив
    generate_random_array(arr, ARRAY_SIZE);
    double t1 = time_qsort(arr, ARRAY_SIZE);
    printf("Випадкові дані: %.6f сек, коректно: %s\n", t1, is_sorted(arr, ARRAY_SIZE) ? "так" : "ні");

    // Зворотній порядок
    generate_reverse_sorted_array(arr, ARRAY_SIZE);
    double t2 = time_qsort(arr, ARRAY_SIZE);
    printf("Зворотній порядок: %.6f сек, коректно: %s\n", t2, is_sorted(arr, ARRAY_SIZE) ? "так" : "ні");

    // Усі однакові значення
    generate_equal_array(arr, ARRAY_SIZE);
    double t3 = time_qsort(arr, ARRAY_SIZE);
    printf("Однакові значення: %.6f сек, коректно: %s\n", t3, is_sorted(arr, ARRAY_SIZE) ? "так" : "ні");

    free(arr);
    return 0;
}
