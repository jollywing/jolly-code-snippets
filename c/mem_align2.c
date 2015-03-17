
#include <stdio.h>

/* sizeof(Sample) 的结果是多少，5？
   错了，是8。int i 从第5个字节开始存放。
   这就是内存对齐，为了能一次性读出 i 的4个字节。 */
typedef struct{
    char a;
    char b;
    int i;
} Sample;

/* sizeof(Sample1) 的大小是12 */
typedef struct{
    char a;
    int i;
    char b;
} Sample1;

typedef struct{
    char a;
    char b;
    char c;
    short s;
    double d;
} FloatStruct;

int main(int argc, char *argv[])
{
    char a;
    short b;
    printf("a: %p, " "b: %p\n", &a, &b);
    printf("%d\n", sizeof(Sample));
    printf("%d\n", sizeof(Sample1));
    printf("%d\n", sizeof(FloatStruct));
    return 0;
}
