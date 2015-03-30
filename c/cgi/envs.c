
/* create: 2012-11-26 */
/* update: 2012-11-26 */
#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
    int i = 0;
    while(env[i]){
        printf("%d: %s\n", i, env[i]);
        i ++;
    }
    return 0;
}
