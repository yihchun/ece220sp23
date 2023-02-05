#include <stdio.h>
#include <math.h>

float f(float x);

int main() {
  int N, i;
  float a,b, accum, deltax, x;

  printf("What is N? ");
  scanf("%d", &N);
  printf("What is the lower limit? ");
  scanf("%f", &a);
  printf("What is the upper limit? ");
  scanf("%f", &b);

  accum = 0;
  deltax = (b-a)/N;
  for (i=0; i<N; i++) {
    x = a+i*deltax;
    accum += f(x)*deltax;
  }
  printf("The integral from %f to %f of x*x is approximately %f\n",
	 a, b, accum);
  return 0;
}
