#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void list_dir(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char full_path[1024];

    dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо "." та ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Побудова повного шляху до файлу/каталогу
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        printf("%s\n", full_path);

        // Перевірка, чи це каталог
        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            // Рекурсивно обходимо підкаталог
            list_dir(full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_dir(".");
    return 0;
}
