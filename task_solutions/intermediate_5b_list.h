#pragma once

typedef struct list_node {
    struct list_node* next;
    int value;
} list_node;

list_node* list_new_node(int value);
list_node* list_append(list_node* list, int value);
void list_print(list_node* list);
list_node* list_insert(list_node* list, int after_value, int value);
list_node* list_insert_iterative(list_node* list, int after_value, int value);
