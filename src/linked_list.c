#include <stdio.h>
struct node {
    struct node* next;
    int value;
};

int usednodes = 0;
struct node nodes[100];

struct node* new_list(int value) {
    if(usednodes == 99) 
        return NULL;
   
     nodes[usednodes].next = NULL;
    nodes[usednodes].value = value;
    return &nodes[usednodes++];
}

void print(struct node *n) {
    while((*n).next != NULL) {
        printf("%d\n", (*n).value);
        n = (*n).next;
    }
    printf("%d\n", (*n).value);
}

void append(struct node *n, int value) {
    while((*n).next != NULL) {
        n++;
    }
    (*n).next = new_list(value);
}

