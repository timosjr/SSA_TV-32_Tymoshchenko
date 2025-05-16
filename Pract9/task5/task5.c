#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *filename = "/tmp/testfile.txt";

    // 1. Створення файлу від імені звичайного користувача
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Не вдалося створити файл");
        return 1;
    }
    write(fd, "Test data\n", 10);
    close(fd);
    printf("[User] Створено файл %s з правами 644\n", filename);

    printf("=> Тепер виконай від імені root в терміналі:\n\n");
    printf("   sudo chown root %s\n", filename);
    printf("   sudo chmod 600 %s\n", filename);
    printf("\nПісля цього знову запусти цю програму, щоб перевірити доступ.\n");

    // 2. Перевірка доступу до файлу
    printf("\n[User] Перевірка доступу після зміни власника і прав:\n");

    if (access(filename, R_OK) == 0)
        printf("Можна ЧИТАТИ файл\n");
    else
        perror("Читання заборонено");

    if (access(filename, W_OK) == 0)
        printf("Можна ЗАПИСУВАТИ у файл\n");
    else
        perror("Запис заборонено");

    return 0;
}
