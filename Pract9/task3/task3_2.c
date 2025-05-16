#include <stdio.h>

int main() {
    FILE *fp = fopen("backup.txt", "a");
    if (!fp) {
        perror("fopen");
        printf("Не вдалося відкрити файл для запису.\n");
    } else {
        fprintf(fp, "Спроба змінити файл...\n");
        fclose(fp);
        printf("Файл успішно змінено.\n");
    }

    // Спроба видалити файл
    if (remove("backup.txt") != 0) {
        perror("remove");
        printf("Файл НЕ видалено.\n");
    } else {
        printf("Файл успішно видалено.\n");
    }

    return 0;
}
