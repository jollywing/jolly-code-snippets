
#include <assert.h>
#include <string.h>

void my_strcpy(char * dest, const char *src)
{
    int i = 0;
    while(1){
        dest[i] = src[i];
        if(src[i] == '\0'){
            break;
        }
        i ++;
    }
}

char* my_strncpy(char* dest, const char* src, int n)
{
    int i = 0;
    dest[n] = '\0';
    while(n -- > 0){
        dest[i] = src[i];
        if(src[i] == '\0')
            break;
        i++;
    }
    return dest;
}

int main(int argc, char *argv[])
{
    char s[256] = "123";
    my_strcpy(s, "Hello");
    assert(strcmp(s, "Hello") == 0);

    my_strcpy(s, "...");
    assert(strcmp(s, "...") == 0);

    my_strncpy(s, "123456", 5);
    assert(strcmp(s, "12345") == 0);
    my_strncpy(s, "123456", 100);
    assert(strcmp(s, "123456") == 0);
    return 0;
}
