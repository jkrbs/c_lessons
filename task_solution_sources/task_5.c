#include <stdio.h>

int is_prime(int a) {
  for (int b = 2; b < a; b++) {
    if (a % b == 0) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  int p = 2;
  for (;;) {
    if (is_prime(p)) {
      printf("%d\n", p);
    }
    p++;
  }
  return 0;
}

