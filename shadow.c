#include <stdio.h>

int x = 5;

int main() {
  int x = 3;
  int *y = &x;
  printf("x = %d, *y = %d\n", x, *y);
  {
    int x = 2;
    printf("x = %d\n", x);
  }
  printf("x = %d\n", x);
  return 0;
}
