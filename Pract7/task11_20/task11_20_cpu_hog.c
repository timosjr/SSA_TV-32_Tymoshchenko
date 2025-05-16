#include <stdio.h>

int main() {
    volatile unsigned long long counter = 0;
    printf("Навантаження CPU... Натисніть Ctrl+C для зупинки.\n");
    while (1) {
        counter++;
    }
    return 0;
}
