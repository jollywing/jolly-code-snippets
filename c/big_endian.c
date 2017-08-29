#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 1;
    char *p = (char*)&i;
    if(p[0] == 1) {
        printf("little endian\n");
    }
    else {
        printf("big endian\n");
    }
    return 0;
}
