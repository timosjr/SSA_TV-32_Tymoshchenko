#include <stdio.h>

void deep_function() {
    int large_array[10000];  // Великий масив у стеку
    printf("New stack top is near %p\n", &large_array[0]);
}

int main() {
    int local_var = 1;
    printf("Original stack top is near %p\n", &local_var);
    deep_function();
    return 0;
}
