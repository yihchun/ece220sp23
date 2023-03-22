#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_struct {
  char *name;
  int UIN;
} student;

#define MAX_NAME_LENGTH 255

/*
 * # of students
 * for each student:
 *    name
 *    uin
 */

int main() {
  char buf[MAX_NAME_LENGTH+1];
  student *arr;
  student tmp;
  int num_students;
  int i;
  scanf("%d", &num_students);
  
  arr = malloc(sizeof(student) * num_students);
  for (i=0; i<num_students; i++) {
    while (fgetc(stdin) != '\n') ; /* read the newline */
    fgets(buf, MAX_NAME_LENGTH, stdin); /* read the name */
    arr[i].name = malloc(strlen(buf)+1);
    strcpy(arr[i].name, buf);
    arr[i].name[strlen(arr[i].name)-1] = '\0';
    scanf("%d", &arr[i].UIN);
    printf("%s %d\n", arr[i].name, arr[i].UIN);
  }
    
}
