#include <stdio.h>

int main(int argc, char *argv[]){
    int i, count = 0;
    for(i = 1; i <= 200; i++) {
        if (i % 2 == 1 && i % 3 == 1 && i % 5 == 1) {
            printf("%d\n", i);
            count ++;
            if (count == 10) {
                break;
            }
        }
    }
    return 0;
}
