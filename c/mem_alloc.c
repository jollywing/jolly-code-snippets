
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int number;
    printf("How many Integers do you want to generate?");
    scanf("%d", &number);

    // malloc needs to include <stdlib.h>
    // return NULL when failed.
    int * randInts = (int *)malloc(sizeof(int) * number);
    if (!randInts) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // using free() needs to include <stdlib.h>
    free(randInts);
    if(randInts) {
        // %x represents unsigned integer of 十六进制
        printf("The memory referred with %x is now freed.\n", randInts);
        randInts = NULL;
    }
}
