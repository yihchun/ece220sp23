#include <stdio.h>

unsigned int mystrlen(const char *str) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

void mystrcpy(char *dst, const char *src) {
  /* an idiom for string copy */
  while ((*(dst++) = *(src++)))
    ;
  
  /* our implementation of string copy:
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  */
}

void mystrrev(char *ver) {
  const int len = mystrlen(ver)-1;
  const double limit = len/2.0;
  int i;
  char tmp;
  for (i=0; i<limit; i++) {
    tmp = ver[i];
    ver[i] = ver[len-i];
    ver[len-i] = tmp;
  }
}

#define MAX_N 10
int pascal() {
  int choose[MAX_N+1][MAX_N+2];
  int i, j;
  for (i=0; i<=MAX_N; i++) {
    for (j=0; j<=i; j++) {
      if ((j==0) || (j==i)) {
	choose[i][j] = 1;
      } else {
	choose[i][j] = choose[i-1][j-1]+choose[i-1][j];
      }
      printf("%d ", choose[i][j]);
    }
    printf("\n");
  }
}

int *lin_search(const int *haystack, int needle, int len) {
  int i;
  for (i=0; i<len; i++) {
    if (haystack[i] == needle) {
      return haystack+i;
    }
  }
  return NULL;
}

int *bin_search(const int *haystack, int needle, int len) {
  int half;
  while (len) { 
    half = len/2;
    if (haystack[half] == needle)
      return haystack+half; /* same as &haystack[half] */
    if (haystack[half] < needle) {
      haystack += half+1;
      len -= half+1;
    } else {
      len = half;
    }
  }
  return NULL;
}

int main() {
  int midterm_scores[] = {36, 75, 85, 90, 96, 100};
  char buf[128];
  char *p = "another test";
  printf("%p\n", lin_search(midterm_scores, 75, 6));
  printf("%p\n", bin_search(midterm_scores, 75, 6));
  pascal();
  mystrcpy(buf, "Hello World");
  mystrrev(buf);
  printf("%s\n", buf);
  printf("%d\n", mystrlen(buf));
  printf("%d\n", mystrlen(p));
  return 0;
}
