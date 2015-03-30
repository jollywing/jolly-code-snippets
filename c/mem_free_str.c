#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 必须要传指针变量的地址进来，否则不能返回动态内存
void getmemory(char **p)
{
  *p = (char *)malloc(100);
  strcpy(*p, "Hello, the world!");
}

int main(int argc, char *argv[])
{
  char *str = NULL;
  getmemory(&str);
  printf("%s\n", str);
  free(str);

  char szstr[10];
  strcpy(szstr,"0123456789");
  // 结果未知
  printf("%s\n", szstr);
  return 0;
}
