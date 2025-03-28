#include <stdio.h>
#include <stdlib.h>

int main() {
    // Викликаємо realloc з NULL (еквівалентно malloc)
    int *ptr = realloc(NULL, 5 * sizeof(int));
    if (ptr == NULL) {
        printf("Не вдалося виділити пам'ять.\n");
        return 1;
    } else {
        printf("Пам'ять виділена успішно для 5 елементів.\n");
    }

    // Викликаємо realloc з розміром 0 (еквівалентно free)
    int *temp = realloc(ptr, 0);
    if (temp == NULL) {
        printf("Пам'ять успішно звільнена (temp == NULL).\n");
    } else {
        printf("Пам'ять не звільнена, temp != NULL.\n");
        // За допомогою temp перевірте, чи вона була перепризначена
        free(temp);  // Важливо: звільніть пам'ять після перевірки
    }

    return 0;
}
