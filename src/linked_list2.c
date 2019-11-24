#include<stdio.h>
#include<stdlib.h>

struct node{
   int value;
   struct node* next;
};

void append(struct node* node, int value){
    while(node->next != NULL){
      node = node->next;
    }
    node->next = malloc(sizeof(node));
    //TODO: check for null
    node->next->value = value;
    node->next->next = NULL;
}

struct node* init(int value){
    struct node* init = malloc(sizeof(struct node));
    init->value = value;
    init->next = NULL;
    return init;
}

void print(struct node* list) {
    while(list != NULL) {
        printf("%x: %d\n", list, list->value);
        list = list->next;
    }
}

int main(int argc, char** argv){
    struct node* mylist = init(4);
 
    for(int i = 0; i <100; i++){
        append(mylist, i);    
    }
    print(mylist); 
    return 0;
}





