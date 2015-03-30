#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *s1 = "123";
  const char *s2 = "123";
  char const *s3 = "456";
  if(s1 == s2) {
    printf("s1, s2 has the same value.\n");
  }
  else
    printf("s1, s2 has the same value.\n");

  printf("The address pointed by s1: %d\n", s1);

  // 运行时会报错，因为s1指向的是不可更改的全局数据段
  // strcpy(s1, "45");
  // printf("s1 pointed to %s now.\n", s1);

  s1 = (char *)s3;
  printf("The address pointed by s1: %d\n", s1);

  int a = 256;
  int * const b = &a; // 指向整数的指针常量
  int const * c = &a; // 指向整数常量的指针

  //error: assignment of read-only variable ‘b’
  // b = c;
  
  return 0;
}
