#include <unistd.h>
#include <stdio.h>

int main() {
    write(1, (void*)0x0000000000001041, 3);
    printf("main=%p\n", main);
    return 0;
}
