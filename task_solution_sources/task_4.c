#include <stdio.h>

int main() {
  int a, b;
  char op;

  if (scanf("%d%c%d", &a, &op, &b) != 3) {
    printf("use the following input format: [number][operation][number]");
    return -1;
  }

  switch (op) {
  case ('+'): {
    printf("%d\n", a + b);
    break;
  }
  case ('-'): {
    printf("%d\n", a - b);
    break;
  }
  case ('*'): {
    printf("%d\n", a * b);
    break;
  }
  case ('/'): {
    printf("%f\n", (float)a / b);
    break;
  }
  default: {
    printf("use the following input format: [number][operation][number]");
    return -1;
  }
  }
  return 0;
}

