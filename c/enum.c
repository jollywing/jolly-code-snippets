
#include <stdio.h>
#include <assert.h>

enum Season {
    Spring = 0,
    Summer,
    Autumn,
    Winter
};

int main(int argc, char *argv[])
{
    enum Season s = Spring;
    assert(s == 0);
    s = Winter;
    assert(s == 3);
    return 0;
}
