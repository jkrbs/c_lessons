#include <stdio.h>

// this function consumes input until it receives a newline character
// feel free to copy it for future occurences where we might need scanf
void clear_line()
{
    int scratch;
    // fgets reads the contents of the stream in its 3rd argument
    // until it receives a newline or the buffer ist full
    // the buffer (1st arg, we use the bytes of an int here) size is in the
    // 2nd arg. When the buffer is too small fgets stops after filling it and
    // returns NULL. By doing this in a loop we make sure that we eventually
    // consume \n
    while (fgets((char*)&scratch, sizeof(scratch), stdin) == NULL) {
    }
}

int main(void)
{
    int x;
    int e;
    for (;;) {
        e = scanf("%d", &x);
        clear_line();
        if (e == 1) break;
    }
    return 0;
}
