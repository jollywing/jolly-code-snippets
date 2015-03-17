#include <stdio.h>
#include <wchar.h>

int main()
{
    unsigned char a[] = "你好a";
    printf("%d\n", sizeof(a));
    printf("%d\n", strlen(a));
    unsigned short i;
    for (i = 0; i < 2; i++){
        printf("%c", a[i]);
    }
    printf("%s\n", a);
    return 0;
}

