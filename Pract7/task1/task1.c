#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[256];

    // Відкриваємо pipe для читання результатів команди rwho
    fp = popen("rwho", "r");
    if (fp == NULL) {
        perror("Не вдалося виконати команду rwho");
        exit(EXIT_FAILURE);
    }

    // Відкриваємо другий pipe для запису в more
    FILE *more_fp = popen("more", "w");
    if (more_fp == NULL) {
        perror("Не вдалося запустити more");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    // Передаємо дані з rwho до more
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, more_fp);
    }

    // Закриваємо обидва pipe
    pclose(fp);
    pclose(more_fp);

    return 0;
}
