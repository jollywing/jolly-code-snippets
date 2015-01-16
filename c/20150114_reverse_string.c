#include <stdio.h>
#include <string.h>

void reverse_output(const char *s) {
    int len = strlen(s);
    int i;
    for(i = len - 1; i >= 0; i--){
        printf("%c", s[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    const char * strs[] = {"China", "America", "Japan", "French"};
    int i;
    for(i = 0; i < 4; i++) {
        reverse_output(strs[i]);
    }
    return 0;
}
