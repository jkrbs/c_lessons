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

int main()
{
    // create a list of the first 10 integers
    node list;
    node* n = &list;
    for (int i = 1; i <= 10; i++) {
        n->next = malloc(sizeof(node));
        n = n->next;
        n->value = i;
    }

    // then we calculate the sum
    int sum;
    n = &list;
    while (n) {
        printf("+%i\n", n->value);
        sum += n->value;
        n = n->next;
    }
    printf("sum: %i\n", sum);

    // then we free our memory, since we are good cicizens :)
    n = &list;
    while (n->next) {
        free(n);
        n = n->next;
    }
}
