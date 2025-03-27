#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

// Функція для друку стеку викликів
void print_stack_trace() {
    void *buffer[10]; // Буфер для збереження адрес
    int nptrs = backtrace(buffer, 10); // Отримуємо стек викликів
    char **symbols = backtrace_symbols(buffer, nptrs); // Отримуємо імена функцій

    if (symbols == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    printf("Stack trace:\n");
    for (int i = 0; i < nptrs; i++) {
        printf("%s\n", symbols[i]);
    }

    free(symbols); // Очищення пам'яті
}

// Тестові функції для аналізу стеку
void function3() {
    printf("Inside function3()\n");
    print_stack_trace(); // Вивести стек викликів
}

void function2() {
    printf("Inside function2()\n");
    function3();
}

void function1() {
    printf("Inside function1()\n");
    function2();
}

int main() {
    printf("Inside main()\n");
    function1();
    return 0;
}
