#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Робимо pipe неблокуючим
    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    const int buffer_size = 256 * 1024; // 64 KB
    char *buffer = malloc(buffer_size);
    memset(buffer, 'A', buffer_size);

    // Не читаємо з іншого кінця, щоб переповнити pipe
    ssize_t written = write(pipefd[1], buffer, buffer_size);
    if (written == -1) {
        perror("write");
    } else if (written < buffer_size) {
        printf("write() записав лише %zd байт із %d\n", written, buffer_size);
    } else {
        printf("write() успішно записав всі байти\n");
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
