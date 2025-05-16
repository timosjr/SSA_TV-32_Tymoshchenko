#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define INPUT_SIZE 16

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char input[INPUT_SIZE];
    int delete_all = 0;  // Прапорець: видаляти все без підтвердження

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропустити "." і ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Перевірити, що це звичайний файл
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            if (!delete_all) {
                printf("Знайдено файл: %s\n", entry->d_name);
                printf("Видалити цей файл? [y = так, n = ні, a = всі, q = вийти]: ");
                if (!fgets(input, sizeof(input), stdin)) continue;

                if (input[0] == 'q' || input[0] == 'Q') {
                    printf("Вихід.\n");
                    break;
                } else if (input[0] == 'a' || input[0] == 'A') {
                    delete_all = 1;
                } else if (input[0] != 'y' && input[0] != 'Y') {
                    printf("Пропущено.\n\n");
                    continue;
                }
            }

            if (remove(entry->d_name) == 0) {
                printf("Видалено: %s\n\n", entry->d_name);
            } else {
                perror("Помилка видалення");
            }
        }
    }

    closedir(dir);
    return 0;
}
