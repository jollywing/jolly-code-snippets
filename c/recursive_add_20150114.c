
#include <stdio.h>

int add(n){
    if (n == 400) {
        return 400;
    }

    if(n % 3 != 0){
        printf("%d\n", n);
        return n + add(n+1);
    }
    else
        return add(n+1);
}

int main(int argc, char *argv[]){
    printf("result is %d\n", add(200));
    return 0;
}
