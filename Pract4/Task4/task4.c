#include <stdio.h>
#include <stdlib.h>

void example() {
    void *ptr = NULL;
    int n = 10;

    // Імітуємо деякі умови для циклу
    for (int i = 0; i < 3; i++) {
        if (!ptr)
            ptr = malloc(n);  // Виділяємо пам'ять
        if (ptr == NULL) {
            printf("Не вдалося виділити пам'ять!\n");
            return;
        }
        printf("Використовуємо пам'ять: %p\n", ptr);
        
        // Використовуємо пам'ять ptr
    }

    // Тепер можна звільнити пам'ять після завершення використання
    free(ptr);
    printf("Пам'ять звільнена.\n");
}

int main() {
    example();
    return 0;
}

