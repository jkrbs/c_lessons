#include <stdio.h>
struct point{
    int x;
    int y;
    int z;
}; 
int foo(struct point p){
    printf("%i %i %i \n", p.x, p.y, p.z);
}
int main(){ 
    struct point p = {y: 3, x: 5, 12};
    foo(p);
    foo(struct point {1,2,3});
}
