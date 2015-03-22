/* 写出在母串中查找子串出现次数 */
#include <assert.h>

int count_substr(char* str,char* s)
{
    char* s1;
    char* s2;
    int count = 0;
    while(*str!='\0')
    {
        s1 = str;
        s2 = s;
        while(*s2 == *s1&&(*s2!='\0')&&(*s1!='\0'))
        {
            s2++;
            s1++;
        }
        if(*s2 == '\0')
            count++;
        str++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    assert(count_substr("123456", "789") == 0);
    assert(count_substr("hello", "ll") == 1);
    assert(count_substr("abcddcab", "ab") == 2);
    return 0;
}
