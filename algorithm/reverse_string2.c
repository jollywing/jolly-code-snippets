
#include <string.h>
#include <stdio.h>

void reverse_string(char *str)
{
    int i;
    char c;
    int len = strlen(str);
    for(i = 0; i < len/2; i++){
        c = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = c;
    }
}

int main(int argc, char *argv[])
{
    char str[] = "Hello, World!";
    printf("%s ==> ", str);
    reverse_string(str);
    printf("%s\n", str);

    char str1[] = "abcdefgh";
    printf("%s ==> ", str1);
    reverse_string(str1);
    printf("%s\n", str1);
    
    return 0;
}
