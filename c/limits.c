#include <limits.h>
#include <stdio.h>

/* limits.h define mini value and max value for every type:
CHAR_BIT
number of bits in a char
CHAR_MAX
maximum value of type char
CHAR_MIN
minimum value of type char
SCHAR_MAX
maximum value of type signed char
SCHAR_MIN
minimum value of type signed char
UCHAR_MAX
maximum value of type unsigned char
SHRT_MAX
maximum value of type short
SHRT_MIN
minimum value of type short
USHRT_MAX
maximum value of type unsigned short
INT_MAX
maximum value of type int
INT_MIN
minimum value of type int
UINT_MAX
maximum value of type unsigned int
LONG_MAX
maximum value of type long
LONG_MIN
minimum value of type long
ULONG_MAX
maximum value of type unsigned long
*/

/* 怎么输出 unit_max */
int main(int argc, char *argv[])
{
    printf("INT_MIN: %d\n"
            "INT_MAX : %d\n"
            "UINT_MAX: %d\n"
            "UCHAR_MAX: %d\n",
            INT_MIN, INT_MAX, UINT_MAX, UCHAR_MAX);
    return 0;
}
