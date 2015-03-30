#include <stdio.h>

void* memcpy(void* pvTo, const void* pvFrom, size_t size)
{
    char * to = (char *)pvTo;
    char * from = (char *)pvFrom;
    int i = 0;
    for(i = 0; i < size; i++){
        to[i] = from[i];
    }
    return pvTo;
}

int main(int argc, char *argv[])
{
    char dest[255] = "1222";
    const char *src = "123456789";
    memcpy(dest, src, 10);
    printf("%s\n", dest);
    return 0;
}
