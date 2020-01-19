#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "termio.h"

void panic(char* msg)
{
    termio_clear_screen();
    termio_fin();
    fputs(msg, stderr);
    exit(EXIT_FAILURE);
}

int main()
{
    if (termio_init()) panic("terminal setup failed");
    int i = 0;
    while (true) {
        printf("fooooo %i", i);
        printf("\r");
        i++;
        char c;
        if (termio_getch(&c)) {
            printf("\r%x      \n", c);
            if (c == 'q') {
                termio_fin();
                return EXIT_SUCCESS;
            }
        }
    }
}
