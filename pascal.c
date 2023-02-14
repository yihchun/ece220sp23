#include <stdio.h>

#define MAX_N 10
#define INDEX(i,j) ((((i)*((i)+1))/2)+(j))
int main() {
  int arr[(MAX_N+2)*(MAX_N+1)/2];
  /* 1    1    1   1   2   1 1 3 3 1 ... */
  /* 0-0 1-0 1-1  2-0 2-1 2-2 ... */
  /* What index does the i-th row start on?
   * in other words, where does i-choose-0 live?
   * (i*(i+1))/2
   * i-choose-j should live at index
   * (i*(i+1))/2+j
   * as long as 0 <= j <= i
   */
  int i, j;
  for (i=0; i<=MAX_N; i++) {
    for (j=0; j<=i; j++) {
      if ((j == 0) || (j==i)) {
	/* arr[(i*(i+1))/2+j] = 1; */
	arr[INDEX(i,j)] = 1;
      } else {
	/* arr[(i*(i+1))/2+j] = arr[((i-1)*i)/2+j-1] + arr[((i-1)*i)/2+j]; */
	arr[INDEX(i,j)] = arr[INDEX(i-1,j-1)]+ arr[INDEX(i-1,j)];
      }
      printf("%d ", arr[(i*(i+1))/2+j]);
    }
    printf("\n");
  }
  return 0;
}
