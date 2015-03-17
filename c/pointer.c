#include <stdio.h>

void g(int**);

int main(int argc, char *argv[])
{
  int line[10], i;
  // line should be equal to &line[0];
  int *p= line; //整型数组的地址退化成指针

  for(i=0; i< 10; i++){
    *p=i; // line[0] = i;
    g(&p);//数组对应的值加 1
  }

  for(i=0;i<10;i++)
    printf("%d\n", line[i]);

  return 0;
}

void g(int**p)
{
  (**p)++;
  (*p)++;
}
