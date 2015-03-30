/**
 * Which of the following statements describe the results
 * of executing the code snippet below in c++?
 */
#include <stdio.h>

int i = 1;
void main(){
    int i = i;
    printf("%d\n", i);
}

/**
 * A. The i within main will have an undefined value
 * B. The i within main will have a value of 1
 * C. The compiler will not allow this statement.
 * D. The i within main will have a value of 0
 *
 * The answer is: A.
 * When a variable is declared, its value is undefined.
 */
