
#include <string.h>
#include <stdio.h>

int main(void) {
    /* !!! strsep 会吧原字符串中的分隔符替换成 \0,
     * 因此如果你要分割的字符串是个常量，会发生段错误. */
    char s[256] = "good,bad,ugly";

    char *p = s;
    /* char *token; */
    /* while((token = strsep(&p, ",")) != NULL){ */
    /*     printf("%s\n", token); */
    /* } */

    while(p) {
        /* token = strsep(&p, ","); */
        printf("%s\n", strsep(&p, ","));
    }
    return 0;
}
