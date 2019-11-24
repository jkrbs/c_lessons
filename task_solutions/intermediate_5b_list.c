#include "intermediate_5b_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

list_node* list_new_node(int value)
{
    list_node* newnode = malloc(sizeof(list_node));
    assert(newnode);
    newnode->next = NULL;
    newnode->value = value;
    return newnode;
}

list_node* list_append(list_node* list, int value)
{
    list_node* newnode = list_new_node(value);
    if (list == NULL) return newnode;
    struct list_node* curr = list;
    while ((*curr).next != NULL) {
        curr = curr->next;
    }
    curr->next = newnode;
    return list;
}

void list_print(list_node* list)
{
    printf("{");
    while (list) {
        printf("%d", list->value);
        list = list->next;
        if (list) printf(", ");
    }
    puts("}");
}

// Lesson 5 Intermediate Task
list_node* list_insert(list_node* list, int after_value, int value)
{
    // TODO: insert a new list node with value "value" after the first list node
    // of value "after_value".
    // if no element has that value, insert at the end of the list
    if (list == NULL) return list_new_node(value);
    if (list->value == after_value) {
        list_node* n = list_new_node(value);
        n->next = list->next;
        list->next = n;
    }
    else {
        list->next = list_insert(list->next, after_value, value);
    }
    return list;
}
