
#include <assert.h>

const float EPSILON = 0.00001;

unsigned char float_equal(float f1, float f2)
{
    float delta = f1 - f2;
    if (delta >= -EPSILON && delta <= EPSILON)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{

    float f1 = 22.12345;
    float f2 = 22.12344;
    float f3 = 11.12345;
    assert(float_equal(f1, f2));
    assert(float_equal(f2, f1));
    assert(!float_equal(f2, f3));
    return 0;
}
