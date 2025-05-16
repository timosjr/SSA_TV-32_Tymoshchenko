#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

#define MAX_LINE 256

int is_executable_by_owner(const struct stat *st) {
    return (st->st_mode & S_IXUSR);
}

int is_owned_by_current_user(const struct stat *st) {
    return st->st_uid == getuid();
}

void ask_and_set_permission(const char *filename, const struct stat *st) {
    char answer[MAX_LINE];
    printf("Файл: %s\n", filename);
    printf("Надати іншим дозвіл на читання (o+r)? [y/n]: ");
    if (fgets(answer, sizeof(answer), stdin)) {
        if (answer[0] == 'y' || answer[0] == 'Y') {
            mode_t new_mode = st->st_mode | S_IROTH;
            if (chmod(filename, new_mode) == 0) {
                printf("Дозвіл на читання надано.\n\n");
            } else {
                perror("chmod");
            }
        } else {
            printf("Пропущено.\n\n");
        }
    }
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat st;

    printf("Пошук виконуваних програм, створених поточним користувачем...\n\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_REG) continue; // лише звичайні файли

        if (stat(entry->d_name, &st) != 0) continue;

        if (is_executable_by_owner(&st) && is_owned_by_current_user(&st)) {
            ask_and_set_permission(entry->d_name, &st);
        }
    }

    closedir(dir);
    return 0;
}
