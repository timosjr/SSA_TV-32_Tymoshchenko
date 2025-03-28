#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "dice_results.txt"
#define MAX_FILE_SIZE 128

void roll_dice_and_write() {
    FILE *file;
    struct stat file_stat;

    int dice_roll = rand() % 6 + 1;

    if (stat(FILENAME, &file_stat) == 0 && file_stat.st_size >= MAX_FILE_SIZE) {
        printf("File exceeded %d bites, clean it...\n", MAX_FILE_SIZE);
        file = fopen(FILENAME, "w");
    } else {
        file = fopen(FILENAME, "a");
    }

    if (file == NULL) {
        perror("Error: can not open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Rolling: %d\n", dice_roll);
    fclose(file);

    printf("Dice roll: %d (written to file)\n", dice_roll);
}

int main() {
    srand(time(NULL));
    char choice;

    do {
        roll_dice_and_write();
        printf("Throw again? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("The game is over. The results are saved to %s\n", FILENAME);
    return 0;
}
