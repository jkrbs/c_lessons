#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Cleaned up Version of the Code we wrote during the last lessons.
// Use this during the Task

typedef struct list_node {
    struct list_node* next;
    int value;
} list_node;

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

// Lesson 5 Intermediate Task
list_node* list_insert_iterative(list_node* list, int after_value, int value)
{
    // TODO: insert a new list node with value "value" after the first list node
    // of value "after_value".
    // if no element has that value, insert at the end of the list
    list_node* newnode = list_new_node(value);
    if (!list) return newnode;
    list_node* i = list;
    while (i->next) {
        if (i->value == after_value) {
            newnode->next = i->next;
            i->next = newnode;
            return list;
        }
        i = i->next;
    }
    i->next = newnode;
    return list;
}

// Test Code
int main(int argc, char* argv)
{
    puts("building list:");
    list_node* list = NULL;
    for (int i = 1; i <= 3; i++) {
        list = list_append(list, i);
    }
    list_print(list);

    puts("inserting:");
    for (int i = 1; i <= 3; i++) {
        list = list_insert_iterative(list, i, -i);
        list_print(list);
    }
    int i = 0;
    for (list_node* n = list; n != NULL; n = n->next) {
        assert(n->value == (-2 * (i % 2) + 1) * (i++ / 2 + 1));
    }
    puts("success!");
    return 0;
}
