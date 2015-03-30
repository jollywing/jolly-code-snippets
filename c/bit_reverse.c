
#include <stdio.h>

int main(int argc, char *argv[])
{
  unsigned short a = 10;
  printf("~a = %d\n", (short) ~a);
  printf("~a = %u\n", ~a);
  return 0;
}
