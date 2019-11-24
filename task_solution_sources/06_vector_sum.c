#include <stdio.h>

// taken from the last exercises
struct node {
    struct node* next;
    int value;
};

struct node nodes[100];
int usednodes = 0;

struct node* append(struct node* n, int value)
{
    if (usednodes == 99) return NULL;
    nodes[usednodes].next = NULL;
    nodes[usednodes].value = value;
    usednodes++;
    if (n == NULL) return &nodes[usednodes - 1];
    struct node* curr = n;
    while ((*curr).next != NULL) {
        curr = curr->next;
    }
    curr->next = &nodes[usednodes - 1];
    return n;
}

void clear_line()
{
    int scratch;
    while (fgets((char*)&scratch, sizeof(scratch), stdin) == NULL) {
    }
}

// actual exercise code starts here
void print_vector(struct node* n)
{
    for (int i = 1; n != NULL; i++) {
        printf("Value %d: %d\n", i, (*n).value);
        n = (*n).next;
    }
}

struct node* input_vector()
{
    struct node* vector = NULL;
    for (int i = 1;; i++) {
        printf("Value %d: ", i);
        int value;
        int e = scanf("%d", &value);
        clear_line();
        if (e != 1) break;
        vector = append(vector, value);
    }
    return vector;
}

int main(void)
{
    puts("This programm calculates the sum of two vectors");
    puts("Please enter the first vector (stops if input isn't a number)");
    struct node* vec1 = input_vector(1);
    puts("Please enter the second vector (stops if input isn't a number)");
    struct node* vec2 = input_vector(2);
    struct node* sum = NULL;
    while (vec1 && vec2) {
        sum = append(sum, vec1->value + vec2->value);
        vec1 = vec1->next;
        vec2 = vec2->next;
    }
    if (vec1 || vec2) {
        puts("Error! Your input vectors don't have the same dimension");
        return -1;
    }
    puts("Sum:");
    print_vector(sum);
    return 0;
}
