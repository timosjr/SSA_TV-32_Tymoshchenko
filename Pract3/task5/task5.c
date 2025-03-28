#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_FILE_SIZE 1048576 // Максимальний розмір файлу (1 МБ)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    const char *source_file = argv[1];
    const char *dest_file = argv[2];

    struct stat file_stat;
    if (stat(source_file, &file_stat) != 0) {
        printf("Cannot open file %s for reading\n", source_file);
        return 1;
    }

    if (file_stat.st_size > MAX_FILE_SIZE) {
        printf("File %s exceeds the maximum allowed size\n", source_file);
        return 1;
    }

    FILE *src = fopen(source_file, "rb");
    if (!src) {
        printf("Cannot open file %s for reading\n", source_file);
        return 1;
    }

    FILE *dest = fopen(dest_file, "wb");
    if (!dest) {
        printf("Cannot open file %s for writing\n", dest_file);
        fclose(src);
        return 1;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            printf("Error writing to file %s\n", dest_file);
            fclose(src);
            fclose(dest);
            return 1;
        }
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully!\n");
    return 0;
}
