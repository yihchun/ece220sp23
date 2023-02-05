#include <stdio.h>

int main() {
  int ascii = 33;
  
  /* loop through all characters 0..127 */
  while (ascii < 128) {
    printf("%3d %c ", ascii, ascii);
    /* put in a newline every 13 characters
     * we know its time for a newline when 13 divides the ascii value minus 32
     */
    if (ascii % 13 == 32 % 13) {
      printf("\n");
    }
    ascii++;
  }
  printf("\n");
  
  ascii = 33;
  do {
    printf("%3d %c ", ascii, ascii);
    if (ascii % 13 == 32 % 13) {
      printf("\n");
    }
    ascii++;
  } while (ascii < 128);
  printf("\n");

  for (ascii=33; ascii <= 0127; ascii++) {
    printf("%3d %c ", ascii, ascii);
    if (ascii % 13 == 32 % 13) {
      printf("\n");
    }
  }  
  printf("\n");
      
  return 0;
}
