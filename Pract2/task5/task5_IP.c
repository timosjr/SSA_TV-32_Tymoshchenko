#include <stdio.h>

void foo() {
    printf("Inside foo()\n");
}

int main() {
    foo();  // Виклик функції (процесор зберігає IP у стеку)
    printf("Back in main()\n");
    return 0;
}
