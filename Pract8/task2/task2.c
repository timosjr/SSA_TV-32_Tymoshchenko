#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "test.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    // Створюємо файл і записуємо туди байти
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for write");
        return 1;
    }
    write(fd, data, sizeof(data));
    close(fd);

    // Відкриваємо файл для читання
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open for read");
        return 1;
    }

    // Переміщуємося до 4-го байта (індекс 3)
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Зчитуємо 4 байти в буфер
    ssize_t bytesRead = read(fd, buffer, 4);
    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    // Виводимо байти буфера
    printf("Буфер після read(): ");
    for (ssize_t i = 0; i < bytesRead; ++i) {
        printf("%u ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
