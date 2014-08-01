
#include "stdio.h"
#include <string.h>

void show_bytes(unsigned char *p, int len)
{
    int i;
    for(i = 0; i < len; i++){
        /* occupy 4 field, supplemented with SPACE */
        /* printf("%4x", p[i]); */
        /* occupy 2 field, supplemented with 0 */
        printf("0x%.2x ", p[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char * str = "ABCDE";
    show_bytes(str, strlen(str));
    return 0;
}
