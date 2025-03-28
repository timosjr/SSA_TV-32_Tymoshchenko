#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int field1; // Приклад поля
    float field2; // Приклад іншого поля
};

int main() {
    struct sbar *ptr, *newptr;

    // Виділяємо пам'ять для 1000 елементів структури
    ptr = calloc(1000, sizeof(struct sbar));
    if (ptr == NULL) {
        // Якщо calloc не зміг виділити пам'ять
        fprintf(stderr, "Error: can not allocate memory\n");
        return 1;
    }

    // Виведемо для перевірки, що пам'ять виділена
    printf("Memory for 1000 elements allocated succesfully\n");

    // Використовуємо reallocarray для зміни розміру пам'яті
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        // Якщо reallocarray не вдалося перевиділити пам'ять
        fprintf(stderr, "Error: can not allocate memory\n");
        free(ptr); // Звільняємо стару пам'ять
        return 1;
    }

    // Виведемо для перевірки, що пам'ять була успішно перевиділена
    printf("Memory for 500 elements allocated succesfully\n");

    // Приклад використання пам'яті
    newptr[0].field1 = 10;
    newptr[0].field2 = 20.5f;

    printf("field1 = %d, field2 = %.2f\n", newptr[0].field1, newptr[0].field2);

    // Звільняємо пам'ять після використання
    free(newptr);

    return 0;
}
