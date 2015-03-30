
// using rand() and srand() need include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int seed;
    printf("Input a integer as random seed: ");
    scanf("%d", &seed);
    printf("Your seed is %d.\n", seed);
    srand(seed);
    
    printf("The 10 random integers (0-15) generated are:\n");
    int i = 0;
    for(; i < 10; i++) {
        printf("%d: %d\n", i + 1, rand() % 16);
    }
    
    return 0;
}
