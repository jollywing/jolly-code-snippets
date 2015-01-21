#include <stdio.h>

void String_cat(char* dest, const char* str) {

    int count = 0;

    while (dest[count]) {

        count ++;

    }

    while ((*(dest+count++) = *str++));

}

int main()
{
    char *s1 = "Hello, world!";
    char s2[15] = "I feel Good!";
    String_cat(s2, s1);
    printf("%s\n", s2);
    return 0;
}
