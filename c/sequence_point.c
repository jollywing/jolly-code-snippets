
#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 5;
    /* ?会产生序列点，因此它左边的表达式要求值完毕，副作用生效后才继续进行右边。 */
    int b = a++ > 5? 0 : a;
    printf("%d\n", b);

    int i = 3;
    int ans = (i++) + (i++) + (i++);
    printf("ans:%d; i:%d\n", ans, i);
    return 0;
}
