#include <stdio.h>
#include <stdlib.h>

void example() {
    int *arr = malloc(5 * sizeof(int));  // Спочатку виділяємо пам'ять
    if (arr == NULL) {
        printf("Не вдалося виділити пам'ять!\n");
        return;
    }

    // Імітуємо ситуацію, де realloc не може виділити пам'ять
    int *new_arr = realloc(arr, 1000000000 * sizeof(int));  // Спробуємо виділити занадто багато пам'яті
    if (new_arr == NULL) {
        printf("Error realloc: can not allocate memory\n");
        free(arr);  // Звільняємо стару пам'ять
        return;
    }

    // Якщо realloc успішний
    printf("Memory allocated\n");

    free(new_arr);  // Звільняємо пам'ять
}

int main() {
    example();
    return 0;
}
