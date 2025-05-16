#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Виконання команди whoami ===\n");
    int res1 = system("whoami");

    if (res1 == -1) {
        perror("Помилка виконання whoami");
        return 1;
    }

    printf("\n=== Виконання команди id ===\n");
    int res2 = system("id");

    if (res2 == -1) {
        perror("Помилка виконання id");
        return 1;
    }

    return 0;
}
