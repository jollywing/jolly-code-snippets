
#include <stdio.h>

// The size of array
/* int size_of_str_array(char ** str_array) */
/* { */
/*   int i = 0; */
/*   while (str_array[i] != NULL) { */
/*     printf("%d\t%s\n", i, str_array[i]); */
/*     i ++; */
/*   } */
/*   return i; */
/* } */

int main(int argc, char *argv[]) {
  char * names[4] = {"Yang", "Man", "John", "Sheep"};
  // int size = size_of_str_array(names);
  int size = sizeof names / sizeof(char *);
  printf("There are %d names in total.\n", size);

  int i;
  for (i = 0; i < size; i++) {
    printf("%d:\t%s\n", i+1, names[i]);
  }
  return 0;
}
