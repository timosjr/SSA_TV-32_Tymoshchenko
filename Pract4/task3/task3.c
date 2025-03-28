#include <stdio.h>
#include <stdlib.h>

int main() {
    void* ptr0 = malloc(0);
    
    if (ptr0 == NULL) {
        printf("malloc(0) повернув NULL\n");
    } else {
        printf("malloc(0) повернув вказівник: %p\n", ptr0);
    }

    void* ptr3 = malloc(3);
    
    if (ptr3 == NULL) {
        printf("malloc(3) повернув NULL\n");
    } else {
        printf("malloc(3) повернув вказівник: %p\n", ptr3);
    }

    free(ptr0);
    free(ptr3);

    return 0;
}
