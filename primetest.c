#include <stdio.h>

int main() {
  int n, i, j;

  printf("Enter an integer: ");
  scanf("%d", &n);

  for (i=2; i<=n; i++) {
    for (j=2; j*j<i; j++) {
      if (!(i%j)) { /* i | j */
	break;
      }
    }
    if (j*j>i) {
      printf("%d is prime\n", i);
    }
  }

  return 0;
}
