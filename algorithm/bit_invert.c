#include <stdio.h>

/**
 * 实现对 x 的进行转换,p 为起始转化位,n 为需要转换的长度,
 * 假设起始点在右边.如 x=0b0001 0001,p=4,n=3 转换后 x=0b0110 0001
 */
unsigned int invert(unsigned int x,int p,int n)
{
  unsigned int a = 1;
  unsigned int t = 0;
  unsigned int i;
  for(i = 0; i < n; i++){
    t |= a;
    a = a << 1;
  }
  t << p;
  x ^= t;
  return x;
}

int main(int argc, char *argv[])
{
  unsigned int i, p, n;
  printf("Input a unsigned integer:");
  scanf("%d", &i);

  do {
    printf("\nInput the position start from right (0 - 31):");
    scanf("%d", &p);
  } while (p < 0 || p > 31);

  do {
    printf("\nInput the bit number to invert (position + bit_number < 32):");
    scanf("%d", &n);
  } while (n <= 0 || p + n > 32);

  i = invert(i, p, n);
  printf("\nThe inverted result is: %d\n", i);

  return 0;
}
