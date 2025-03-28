#include <stdio.h>

void recursive_function(int depth) {
    printf("Recursion depth: %d\n", depth);
    recursive_function(depth + 1);
}

int main() {
    printf("Starting recursive function...\n");
    recursive_function(1);
    return 0;
}
