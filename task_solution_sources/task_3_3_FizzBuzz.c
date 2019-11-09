#include <stdio.h>

int main(void) {
    int i = 0;
    while (i <100) {
        int b = i%3 + 2 * (i % 5);
        if (b == 0) {
            printf("%i", i);
        } else if (b == 1) {
            puts("Fizz");
        } else if (b == 2) {
            puts("Buzz");
        } else if (b == 3) {
            puts("FizzBuzz");
        }
        i++; 
    }
}
