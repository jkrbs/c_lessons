#include <stdio.h>

void clear_line() // copied from scanf example. See there for a full explanation
{
    int scratch;
    while (fgets((char*)&scratch, sizeof(scratch), stdin) == NULL) {
    }
}

int main(void)
{
    // lhs stands for left hand side of equation. common abbreviation in code.
    // and especially in parsers / compilers. rhs analoguously.
    float lhs;
    float rhs;
    char op;

    for (;;) {
        puts("Please enter a simple math expression:");
        int e = scanf("%f %c %f", &lhs, &op, &rhs);
        clear_line();
        if (e != 3) {
            puts("Failed to parse your input.");
            continue;
        }
        switch (op) {
            case '+':
                printf("%.5g + %.5g = %.5g\n", lhs, rhs, lhs + rhs);
                return 0;
            case '-':
                printf("%.5g - %.5g = %.5g\n", lhs, rhs, lhs - rhs);
                return 0;
            case '*':
                printf("%.5g * %.5g = %.5g\n", lhs, rhs, lhs * rhs);
                return 0;
            case '/':
                printf("%.5g / %.5g = %.5g\n", lhs, rhs, lhs / rhs);
                return 0;
            default: printf("Unknown operator '%c'", op); break;
        }
    }
    return 0;
}
