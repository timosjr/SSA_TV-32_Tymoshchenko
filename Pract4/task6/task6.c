#include <stdio.h>
#include <stdlib.h>

int main() {
    // Викликаємо realloc з NULL (еквівалентно malloc)
    int *ptr = realloc(NULL, 5 * sizeof(int));
    if (ptr == NULL) {
        printf("Can not allocate memory\n");
        return 1;
    } else {
        printf("Memory allocated\n");
    }

    // Викликаємо realloc з розміром 0 (еквівалентно free)
    int *temp = realloc(ptr, 0);
    if (temp == NULL) {
        printf("Memory free\n");
    } else {
        printf("Memory not free, temp != NULL.\n");
        // За допомогою temp перевірте, чи вона була перепризначена
        free(temp);  // Важливо: звільніть пам'ять після перевірки
    }

    return 0;
}
