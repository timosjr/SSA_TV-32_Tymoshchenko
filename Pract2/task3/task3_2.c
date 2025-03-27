#include <stdio.h>
#include <stdlib.h>

int global_var = 42;  // Потрапляє в сегмент .data
int uninitialized_var; // Потрапляє в сегмент .bss

void function() {} // Потрапляє в сегмент .text

int main() {
    int local_var = 123;  // У стеку
    int *heap_var = (int*) malloc(sizeof(int)); // У купі (heap)

    printf("Address of function (text segment): %p\n", function);
    printf("Address of initialized global variable (.data): %p\n", &global_var);
    printf("Address of uninitialized global variable (.bss): %p\n", &uninitialized_var);
    printf("Address of heap variable (heap): %p\n", heap_var);
    printf("Address of local variable (stack): %p\n", &local_var);

    free(heap_var);
    return 0;
}
