#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define assert(con) do { \
    if(!(con)) { \
        fprintf(stderr, "%s:%d: %s: Assertion '%s' failed\n", __FILE__, __LINE__, __FUNCTION__, #con); \
        abort(); \
    } \
} while(0)


int main() {
    assert(1 == 2);
    exit(0);
}
