#include<stdio.h>
#include<stdlib.h>


struct node {
    struct node* l;
    struct node* r;
    int value;
};

int id = 0;

struct node* generate(struct node* parent, int depth) {
    if (depth == 0)
        return NULL;
    parent->l = malloc(sizeof(struct node));
    parent->r = malloc(sizeof(struct node));
    parent->value = id++;
    generate(parent->l, depth-1);
    generate(parent->r, depth-1);   
    
    return parent;
}

void free_tree(struct node* tree) {
    if(tree == NULL)
        return;
    free_tree(tree->l);
    free_tree(tree->r);
    free(tree);
    return;
}
int tree_sum(struct node* tree) {
    if(tree == NULL)
        return 0;
    return tree->value + tree_sum(tree->r) + tree_sum(tree->l);
}


int main(int argc, char** argv) {
    int depth = atoi(argv[1]);
   
    struct node* tree = malloc(sizeof(struct node));
    generate(tree, depth);

    printf("sum:%d\n", tree_sum(tree));
    free_tree(tree);
    return 0;
}

