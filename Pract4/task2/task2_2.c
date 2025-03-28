#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    // Визначимо два числа для множення
    int xa = 2;
    int xb = MAX_INT;
    
    int num = xa * xb;
    
    // Перевіряємо на переповнення
    if (num < 0) {
        printf("Owerflow completed\n");
    } else {
        printf("Number of bites for malloc: %d\n", num);
        
        void* ptr = malloc(num);
        
        if (ptr == NULL) {
            printf("Can not allocate memory\n");
        } else {
            printf("Memory allocated\n");
            free(ptr);
        }
    }

    return 0;
}
