#include <stdio.h>
#include <stdlib.h>

// this is a fairly nonsensical program that builds up a linked list of integers
// and than adds up their sum. it contains multiple errors that you should
// attempt to fix using valgrind. whether it works initially may depend on your
// machine, since it uses undefined behaviour

// simple linked list node
typedef struct node {
    int value;
    struct node* next;
} node;

int main(int argc, char** argv)
{
    // create a list of the first 10 integers
    node* list; // no element on the stack, only makes things less ergonomic
    node** tail = &list; // points to the last next pointer (may be the start)
    for (int i = 1; i <= 10; i++) {
        *tail = malloc(sizeof(node));
        (**tail).value = i;
        tail = &(**tail).next;
    }
    *tail = NULL; // remember to set the last next to NULL!

    // then we calculate the sum
    int sum = 0;
    for (node* n = list; n != NULL; n = n->next) {
        printf("+%i\n", n->value);
        sum += n->value;
    }
    printf("sum: %i\n", sum);

    // then we free our memory, since we are good cicizens :)
    node* n = list;
    while (n) {
        node* f = n;
        n = n->next; // we need to access n->next BEFORE freeing n
        free(f);
    }

    return 0;
}
