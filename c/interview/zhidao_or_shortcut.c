#include <stdio.h>

int main() {
    int x=2,y=2,z=0,a;
    a=++x||++y&&z++;
    printf("%d,%d,%d\n",x,y,z); /* 3, 2, 0 */
    printf("%x\n", 2913);
    return 0;
}
