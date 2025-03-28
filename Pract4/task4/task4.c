#include <stdio.h>
#include <stdlib.h>

void example() {
    void *ptr = NULL;
    int n = 10;

    for (int i = 0; i < 3; i++) {
        if (!ptr)
            ptr = malloc(n);
        if (ptr == NULL) {
            printf("Can not allocate memory\n");
            return;
        }
        printf("Using memory: %p\n", ptr);
        
    }

    free(ptr);
    printf("Memory free\n");
}

int main() {
    example();
    return 0;
}


