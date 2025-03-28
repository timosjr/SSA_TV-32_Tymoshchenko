#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define MAX_TIME 5 // Ліміт часу на виконання (у секундах)
#define LOTTERY_1_SIZE 7
#define LOTTERY_2_SIZE 6

// Обробка сигналу при перевищенні ліміту часу
void handle_alarm(int sig) {
    printf("Execution time has expired. Program is finished.\n");
    exit(1);
}

// Функція для генерації унікальних випадкових чисел
void generate_unique_numbers(int *arr, int size, int min, int max) {
    int i, num, j, unique;

    for (i = 0; i < size; i++) {
        do {
            num = rand() % (max - min + 1) + min;
            unique = 1;
            for (j = 0; j < i; j++) {
                if (arr[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        arr[i] = num;
    }
}

// Функція для сортування масиву чисел (для кращої візуалізації)
void sort_numbers(int *arr, int size) {
    int temp, i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    signal(SIGALRM, handle_alarm);  // Встановлюємо обробник сигналу для обмеження часу
    alarm(MAX_TIME);  // Встановлюємо таймер для сигналу через MAX_TIME секунд

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    int lottery_1[LOTTERY_1_SIZE];
    int lottery_2[LOTTERY_2_SIZE];

    // Генерація 7 чисел з діапазону 1-49
    generate_unique_numbers(lottery_1, LOTTERY_1_SIZE, 1, 49);
    // Генерація 6 чисел з діапазону 1-36
    generate_unique_numbers(lottery_2, LOTTERY_2_SIZE, 1, 36);

    // Сортуємо числа для зручності виведення
    sort_numbers(lottery_1, LOTTERY_1_SIZE);
    sort_numbers(lottery_2, LOTTERY_2_SIZE);

    // Виведення результатів
    printf("Lottery result (7 out of 49): ");
    for (int i = 0; i < LOTTERY_1_SIZE; i++) {
        printf("%d ", lottery_1[i]);
    }
    printf("\n");

    printf("Lottery result (6 out of 36): ");
    for (int i = 0; i < LOTTERY_2_SIZE; i++) {
        printf("%d ", lottery_2[i]);
    }
    printf("\n");

    return 0;
}
