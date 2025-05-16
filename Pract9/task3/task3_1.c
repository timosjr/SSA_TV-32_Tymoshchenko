#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *user = getenv("SUDO_USER"); // логін звичайного користувача
    if (!user) {
        fprintf(stderr, "Запустіть програму через sudo, щоб отримати SUDO_USER\n");
        return 1;
    }

    char path1[256], path2[256];
    snprintf(path1, sizeof(path1), "/home/%s/original.txt", user);
    snprintf(path2, sizeof(path2), "/home/%s/backup.txt", user);

    // Створення файлу від імені звичайного користувача (симуляція)
    FILE *fp = fopen(path1, "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Це тестовий файл.\n");
    fclose(fp);

    // Копіювання файлу як root
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cp %s /tmp/root_copy.txt", path1);
    system(cmd);

    // Зміна прав власника
    system("chown root:wheel /tmp/root_copy.txt");

    // Копіювання назад у домашню директорію
    snprintf(cmd, sizeof(cmd), "cp /tmp/root_copy.txt %s", path2);
    system(cmd);

    printf("Файл скопійовано як root. Перевіримо дії користувача.\n");

    return 0;
}
