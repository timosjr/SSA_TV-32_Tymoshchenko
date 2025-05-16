#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "testfile.txt";

    // Створимо файл і запишемо стартовий вміст
    int fd_init = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_init < 0) {
        perror("open for init");
        return 1;
    }
    write(fd_init, "HelloWorld", 10); // 10 байт
    close(fd_init);

    // Відкриємо файл двічі з різними дескрипторами
    int fd1 = open(filename, O_RDONLY);
    int fd2 = open(filename, O_WRONLY);

    if (fd1 < 0 || fd2 < 0) {
        perror("open");
        return 1;
    }

    // Зчитуємо 5 байт з fd1 (позиція буде 5)
    char buf1[6] = {0};
    read(fd1, buf1, 5);
    printf("Читання з fd1: '%s'\n", buf1);

    // Запис у той самий файл через інший дескриптор
    write(fd2, "ABCDE", 5);  // fd2 має свою позицію → починає з 0

    // Тепер знову читаємо ще 5 байт з fd1 (з позиції 5)
    char buf2[6] = {0};
    read(fd1, buf2, 5);
    printf("Читання з fd1 після запису через fd2: '%s'\n", buf2);

    close(fd1);
    close(fd2);

    return 0;
}
