
#include <stdio.h>

int get_1_count(int x)
{
  int count = 0;
  while(x) {
    count ++;
    x &= x - 1;
  }
  return count;
}

int main(int argc, char *argv[])
{
  int i;
  printf("Input a integer: \n");
  scanf("%d", &i);
  printf("%d contains %d 1\n", i, get_1_count(i));
  return 0;
}
