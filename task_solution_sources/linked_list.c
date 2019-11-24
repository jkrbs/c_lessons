#include <stdio.h>
#include <assert.h>

struct node {
    struct node* next;
    int value;
};

int usednodes = 0;
struct node nodes[100];

struct node* add_node(int value)
{
    // if our array is full, throw an error
    assert(usednodes < 100);
    // initialize a new node and return a pointer to it
    nodes[usednodes].next = NULL;
    nodes[usednodes].value = value;
    // increase usednodes so we don't override next time
    return &nodes[usednodes++];
}

void print(struct node* n)
{
    while (n != NULL) {
        printf("%d\n", (*n).value);
        n = (*n).next;
    }
}

void append_node(struct node* n, int value)
{
    // iterate to the last node
    while ((*n).next != NULL) {
        n++;
    }
    // change that node's next value to a new node
    (*n).next = add_node(value);
}

int main(int argc, char** argv)
{
    // create two lists
    struct node* l1 = add_node(1);
    struct node* l2 = add_node(1);
    // append some nodes
    append_node(l1, 5);
    append_node(l1, 9);
    append_node(l1, 77);
    append_node(l2, 12);
    append_node(l2, 42);
    append_node(l2, 9);
    // print the resulting lists
    puts("list 1:");
    print(l1);
    puts("list 2:");
    print(l2);
    return 0;
}
