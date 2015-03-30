
#include <stdio.h>

typedef char bool;
#define false 0
#define true 1

bool is_2power(int i)
{
  if(i < 0)
    i = -i;
  return (i & (i-1))?false:true;
}

int main(int argc, char *argv[])
{
  int i;
  scanf("%d", &i);
  if(is_2power(i))
    printf("%d is power of 2\n", i);
  else
    printf("%d is not power of 2\n", i);

  return 0;
}
