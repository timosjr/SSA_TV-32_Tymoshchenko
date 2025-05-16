#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_ENTRIES 1024
#define NAME_LEN 256

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char path[NAME_LEN];
    char *dirs[MAX_ENTRIES];
    int count = 0;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо "." та ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Створюємо повний шлях
        snprintf(path, sizeof(path), "./%s", entry->d_name);

        // Перевіряємо, чи це каталог
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            dirs[count] = strdup(entry->d_name);
            if (dirs[count] == NULL) {
                fprintf(stderr, "Помилка виділення пам'яті\n");
                return 1;
            }
            count++;
        }
    }
    closedir(dir);

    // Сортування
    qsort(dirs, count, sizeof(char *), compare);

    // Виведення
    for (int i = 0; i < count; ++i) {
        printf("%s/\n", dirs[i]);
        free(dirs[i]); // звільняємо пам'ять
    }

    return 0;
}
