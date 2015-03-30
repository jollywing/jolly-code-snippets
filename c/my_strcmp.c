
#include <assert.h>

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    while(s1[i] || s2[i]){
        if(s1[i] < s2[i])
            return -1;
        if(s1[i] > s2[i])
            return 1;
        i ++;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    assert(my_strcmp("123", "123") == 0);
    assert(my_strcmp("1234", "123") == 1);
    assert(my_strcmp("1222", "1232") == -1);
}
