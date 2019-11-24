#include<stdio.h>
#include<stdlib.h>

struct tree{
    int value;
    struct tree* left;
    struct tree* right;
};

void print(struct tree* t){
    if(t == NULL) {
        return;
    }
    print(t->left);
    printf("%i\n", t->value);
    print(t->right);
}

struct tree* append_left(struct tree* tree, int value) {
    if(tree == NULL) {
        tree = malloc(sizeof(struct tree));
        tree->left = NULL;
        tree->right = NULL;
        tree->value = value;
        
        return tree;
    }

    tree->left = append_left(tree->left, value);
    return tree;
}

int main(int argc, char** argv) {

    struct tree* tree = append_left(NULL, 0);
    
    for(int i = 1; i<17; i++) {
        tree = append_left(tree, i);
    }

    print(tree);    

    return 0;
}
