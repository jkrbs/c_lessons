#include "intermediate_5b_list.h"
#include <stdio.h>
#include <assert.h>

// compile both files at once using
// gcc intermediate_5_main.c intermediate_5_list.c

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
        list = list_insert(list, i, -i);
        list_print(list);
    }
    int i = 0;
    for (list_node* n = list; n != NULL; n = n->next) {
        assert(n->value == (-2 * (i % 2) + 1) * (i++ / 2 + 1));
    }
    puts("success!");
    return 0;
}
