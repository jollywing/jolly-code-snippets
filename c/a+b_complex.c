#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RECORD_NUM 100

void parse_int(const char *str, int *a)
{
    char t[8];
    int l = strlen(str);
    int i, j = 0;
    int sum = 0, m;

    int sig = 1;

    for(i = 0; i < l; i++){
        if(str[i] == '-'){
            sig *= -1;
        }
        else if(str[i] == ','){
            t[j] = '\0';
            j = 0;
            m = atoi(t);
            sum = sum * 1000 + m;
        }
        else {
            t[j] = str[i];
            j++;
        }
    }

    t[j] = '\0';
    m = atoi(t);
    sum = sum * 1000 + m;
    *a = sum * sig;
}

void parse_a_b(const char *str, int *a, int *b)
{
    int i;
    char a_str[256];
    char b_str[256];

    // printf("record string: %s\n", str);
    /* find space */
    for(i = 0; i < strlen(str); i++){
        if(str[i] == ' ')
            break;
    }
    if (i >= strlen(str)){
        printf("error record format!\n");
        exit(1);
    }
    /* get a string */
    memcpy(a_str, str, i);
    a_str[i] = '\0';
    /* get b string */
    memcpy(b_str, str + i + 1, strlen(str) - 2 - i);
    b_str[strlen(str) - i -2] = '\0';

    // printf("%s %s\n", a_str, b_str);

    /* parse a */
    parse_int(a_str, a);
    /* parse b */
    parse_int(b_str, b);
    // printf("%d %d\n", *a, *b);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int records[RECORD_NUM][2];
    int record_count = 0;
    char line_buf[512];
    int a, b, i;

    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    /* open file */
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Open input file failed!\n");
        exit(2);
    }

    while(!feof(fp)){
        /* get line */
        memset(line_buf, 0, 512);
        fgets(line_buf, 512, fp);
        if(strlen(line_buf) > 0){
            parse_a_b(line_buf, &a, &b);
            records[record_count][0] = a;
            records[record_count][1] = b;
            record_count++;
        }
    }
    fclose(fp);
    /* for each line, output a + b */
    for(i = 0; i < record_count; i++){
        printf("%d\n", records[i][0] + records[i][1]);
    }
    return 0;
}
