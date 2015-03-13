/*
 * CREATE: 20150114
 * update: 2015-03-13 Fri
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void reverse_string(char *s) {
    int len = strlen(s);
    int mid_idx = len / 2;
    int i;
    char c;
    for(i = 0; i < mid_idx; i++){
        c = s[i];
        s[i] = s[len - 1 -i];
        s[len - 1 - i] = c;
    }
}

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

    char s1[] = "Dream is great!";
    reverse_string(s1);
    assert(!strcmp(s1, "!taerg si maerD"));
    char s2[] = "1";
    reverse_string(s2);
    assert(!strcmp(s2, "1"));
    char s3[] = "";
    reverse_string(s3);
    assert(!strcmp(s3, ""));
    return 0;
}
