
#include <stdio.h>

#define swap(x,y) \
  x = x + y;\
  y = x - y;\
  x = x - y

// This is fit for integer and char
#define SWAP(x,y) \
  x = x ^ y;\
  y = x ^ y;\
  x = x ^ y

int main(int argc, char *argv[])
{
  int x = 15;
  int y = 35;
  // int *px = &x, *py = &y;
  swap(x, y);
  printf("x=%d; y=%d\n", x, y);

  char c1 = 'b';
  char c2 = 'x';
  SWAP(c1, c2);
  printf("c1=%c; c2=%c\n", c1, c2);
  return 0;
}
