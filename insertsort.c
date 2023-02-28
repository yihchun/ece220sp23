#include <stdio.h>

void myinsertsort(int *arr, unsigned int len) {
  int i, j, tmp;
  for (i=1; i<len; i++) {
    /* PRE:  [0..i-1] elements are sorted
     * POST: [0..i] elements are sorted
     */
    tmp = arr[i]; /* new element to be sorted */
    /* figure out where to put it
     * loop through the elements before this one, until we reach a spot
     * for the ith element to be placed. In particular, we place it
     * after any value <= to it. (e.g., if arr[j-1] <= tmp < (original) arr[j]
     * then the new place for tmp is at arr[j] (note that arr[j] has already
     * moved to arr[j+1] in a previous iteration).
     * Also, if we run off the beginning of the array (j=0), then this is
     * the smallest element in the array so far, and we place it at index 0,
     * having already shifted [0..i-1] to [1..i].
     */
    for (j=i; j>0; j--) {
      /* loop until when (the original value of)
       * arr[i] becomes greater arr[j-1]
       */
      if (tmp >= arr[j-1]) {
	break;
      }
      arr[j] = arr[j-1]; /* move j-1 to j to make room for either tmp or j-2 */
    }
    /* found the correct spot, update the array to add the ith elt */
    arr[j] = tmp;
  }
}

/* RECURSION */
/* 2. Returns N factorial */
unsigned int factorial(unsigned int N) { /* 1 */
  int tmp;
  if (N <= 1) return 1; /* 3. base case */
  printf("In factorial(%d)\n", N);
  tmp = factorial(N-1); /* 4. make progress, 5. use the force */
  return N*tmp; /* 6. reassemble */
}

/* sort the array arr[0..len-1] in non-descending order */
void myquicksort(int *arr, unsigned int len) {
  int p, i, tmp;
  int *left, *right;
  if (len < 2) return;
  printf("Asking to sort: ");
  for (i=0; i<len; i++)
    printf("%d ", arr[i]);
  printf("\n");
  p = *arr;
  /* perform partition */
  left = arr+1;
  right = arr+len-1;
  for (i=1; i<len; i++) {
    if (arr[i] < p) {
    }
  }
  while (right > left) {
    /* move right leftwards to a location that is < p */
    while ((right >= left) && (*right > p))
      right--;
    
    /* move left rightwards to a location that is > p */
    while ((left <= right) && (*left < p))
      left++;

    if (right < left) break;
    tmp = *right;
    *right = *left;
    *left = tmp;
  }
  /* partition is complete */
  /* p [ <= p ] [ >= p ]      [ <= p ] p [ >= p]
   *         ^R  ^L                    R  L
   * p [ < p           ]      [ < p          ] p
   *                  ^R^L                     R L
   * p [ > p           ]      p [ > p        ] 
   * ^R ^L                    R  L
   */
  printf("%p %p %p\n", arr, left, right);
  arr[0] = *right;
  *right = p;
  myquicksort(arr, right-arr);
  if (len > (left-arr)) 
    myquicksort(left, len-(left-arr));
}

#define SZ 16
int main() {
  /* test harness */
  FILE *fp = fopen("/dev/urandom", "r");
  int i;
  int arr[SZ];
  int tmp[2] = {2,3};
  for (i=0; i<SZ; i++) {
    arr[i] = fgetc(fp);
  }

  /* we magically have our array */
  for (i=0; i<SZ; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  //myquicksort(arr, SZ);
  myquicksort(tmp, 2);
  printf("%d %d\n", tmp[0], tmp[1]);

  for (i=0; i<SZ; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  printf("%d\n", factorial(5));
  return 0;
}

  
