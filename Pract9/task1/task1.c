#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define MAX_LINE 1024
#define UID_THRESHOLD 1000  // Змініть на 500, якщо у вашій системі нижчий поріг

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    uid_t current_uid = getuid();
    int found_other_user = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        // Розділяємо рядок за допомогою strtok
        char *username = strtok(line, ":");
        strtok(NULL, ":"); // Пропускаємо поле паролю
        char *uid_str = strtok(NULL, ":");
        if (!username || !uid_str) continue;

        uid_t uid = (uid_t)atoi(uid_str);

        if (uid >= UID_THRESHOLD && uid != current_uid) {
            printf("Знайдено звичайного користувача: %s (UID: %d)\n", username, uid);
            found_other_user = 1;
        }
    }

    pclose(fp);

    if (!found_other_user) {
        printf("Інших звичайних користувачів, окрім вас (UID %d), не знайдено.\n", current_uid);
    }

    return 0;
}
