#include <stdio.h>

int main(int argc, char * argv[])
{
  if (argc < 2) {
    printf("Usage: %s <fileName>\n", argv[0]);
    return -1;
  }

  char c;
  FILE *fp = fopen(argv[1], "r");
  while (c != EOF) {
    c = getc(fp);
    putchar(c);
  }
  return 0;
}

