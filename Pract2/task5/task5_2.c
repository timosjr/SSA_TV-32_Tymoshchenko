#include <stdio.h>

void hack_return() {
    asm("addq $8, %rsp"); // Зсуває стек, "гублячи" адресу повернення
}

void func() {
    printf("Inside func()\n");
    hack_return(); // Ламає правильне повернення
}

int main() {
    func();
    printf("Back in main()\n"); // Це ніколи не виконається!
    return 0;
}
