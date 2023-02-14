#include <stdio.h>

void noswap(int *pa, int *pb) {
  int tmp;
  tmp = *pa;
  pa = pb;
  pb = &tmp;
  printf("%d %d\n", *pa, *pb);
}

void swap(int *pa, int *pb) {
  int tmp;
  tmp = *pa;
  *pa = *pb;
  *pb = tmp;
  printf("%d %d\n", *pa, *pb);
}

#define LEN 10
int main() {
  int x = 3;
  int y = 4;
  int arr[LEN] = {1,2,3,4,5,6,7,8,9,10};
  int i;
  float sum = 0;
  for (i=0; i<LEN; i++) {
    sum += arr[i];
  }
  printf("The average is %f\n", sum/LEN);  
  
  printf("%d %d\n", x, y);
  swap(&x, &y);
  printf("%d %d\n", x, y);
  return 0;
}
