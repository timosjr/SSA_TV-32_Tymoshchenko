#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_OPERATIONS 1000000

// Структура для кожного потоку
typedef struct {
    int id;
    unsigned long *heap;
} ThreadData;

// Функція для виконання операцій на heap
void *perform_operations(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        data->heap[i % NUM_OPERATIONS] = i;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    unsigned long *heap = malloc(NUM_OPERATIONS * sizeof(unsigned long));
    if (heap == NULL) {
        perror("Failed to allocate heap memory");
        return EXIT_FAILURE;
    }

    clock_t start = clock();

    // Створення потоків
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].id = i;
        thread_data[i].heap = heap;
        if (pthread_create(&threads[i], NULL, perform_operations, (void *)&thread_data[i]) != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    // Очікування завершення потоків
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken with pthreads: %f seconds\n", time_taken);

    free(heap);
    return EXIT_SUCCESS;
}
