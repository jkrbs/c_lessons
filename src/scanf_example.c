#include <stdio.h>

int main(void) {
    int x;
    int e;
    do {
        puts("please enter a valid number:");
        e =scanf("%d", &x);
    } while (e != 1);
    return 0;
}
