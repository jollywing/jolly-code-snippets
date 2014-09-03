
#include <stdio.h>

void test_truncation(){
    printf("Now Let us test Truncation.\n");
    printf("==============================\n");
    int long_num;
    printf("Input a hexadecimal number: ");
    scanf("%x", &long_num);
    printf("The value you have inputed is %d\n", long_num);
    short short_num = long_num;
    printf("Long number become to %x\n", short_num);
    printf("It's decimal value is %d\n", short_num);
    
}

void test_unsigned_convert(){
    /* 0u is a unsigned const */
    /* c will convert -1 to unsigned integer */
    if(-1 > 0u){
        printf("Hello, world!\n");
    }
}

int main(int argc, char *argv[])
{
    test_truncation();
    test_unsigned_convert();
    return 0;
}
