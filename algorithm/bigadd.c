#include <stdio.h>
#include <string.h>

/* 实现任意长度的整数相加或者相乘功能。  */

void bigadd(char* num, char* str, int len)
{
    int i;
    for(i=len; i>0; i--)
    {
        num[i] += str[i];
        int j = i;
        while(num[j]>=10)
        {
            num[j--] -= 10;
            num[j] += 1;
        }
    }
}

int main(int argc, char *argv[])
{
    char s1[256] = "123456";
    char * s2 = "111111111111111";
    bigadd(s1, s2, strlen(s2));
    printf("%s\n", s1);
    return 0;
}
