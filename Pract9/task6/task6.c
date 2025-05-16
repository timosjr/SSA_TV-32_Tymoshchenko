#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void check_access(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("\n--- Вміст %s ---\n", dir_path);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо . і ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        printf("\nФайл: %s\n", path);

        // Статистика про файл
        struct stat sb;
        if (stat(path, &sb) == -1) {
            perror("stat");
            continue;
        }

        printf("  Розмір: %ld байт\n", sb.st_size);

        // Спроби доступу
        if (access(path, R_OK) == 0)
            printf("Читання дозволено\n");
        else
            printf("Читання заборонено\n");

        if (access(path, W_OK) == 0)
            printf("Запис дозволено\n");
        else
            printf("Запис заборонено\n");

        if (access(path, X_OK) == 0)
            printf("Виконання дозволено\n");
        else
            printf("Виконання заборонено\n");
    }

    closedir(dir);
}

int main() {
    printf("Перевірка доступу до файлів\n");

    const char *home = getenv("HOME");
    check_access(home);
    check_access("/usr/bin");
    check_access("/etc");

    return 0;
}
