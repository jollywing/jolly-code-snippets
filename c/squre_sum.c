#include <stdio.h>

int main()
{
    int m, a, b;
    for(m = 100; m <= 200; m++) {
        for(a = 1; a < m; a ++)
            for(b = 1; b < m; b++) {
                if(a * a + b * b == m*m) {
                    printf("%d, %d, %d\n", a, b, m);
                    goto loop;
                }
            }
      loop: continue;
    }
}
