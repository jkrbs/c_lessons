#include <stdio.h>
int main(){
    int i;
    int r = scanf("%i", &i); 
    printf("e: %i\n", ferror());
    printf("r: %i, i: %i\n",r, i);
}
