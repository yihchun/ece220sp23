#include <stdio.h>
#include <assert.h>

int fib_r(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fib_r(n-1) + fib_r(n-2);
}

int fib(int n) {
  int a, b, c, i;
  a = 0;
  b = 1;
  if (n == 0) return 0;
  if (n == 1) return 1;
  for (i=2; i<=n; i++) {
    c = a+b;
    a = b;
    b = c;
  }
  return c;
}


unsigned long choose(unsigned long a, unsigned long b) {
  long afactorial, ambfactorial, bfactorial, i;
  assert(a >= b);
  for (bfactorial = ambfactorial = afactorial=i=1; i<=a; i++) {
    afactorial *= i;
    if (i == b) {
      bfactorial = afactorial;
    }
    if (i == (a-b)) {
      ambfactorial = afactorial;
    }
  }
  
  return afactorial / (ambfactorial * bfactorial);
}

int main() {
  int a, b;
  scanf("%d", &a);
  printf("F_%d = %d\n", a, fib_r(a));
  return 0;
  scanf("%d%d", &a, &b);
  printf("%d choose %d = %lu\n", a, b, choose(a,b));
}
