#include <assert.h>

/* a和b之间留不留空白不影响 */
#define max(a, b) \
    ({__typeof__(a) _a = (a);                   \
    __typeof__(b) _b = (b); \
    _a > _b ? _a: _b;})

#define min(a, b) \
    ({ __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _b: _a; })

int main(int argc, char *argv[])
{
    int a = max(4 * 5, 100);
    assert(a == 100);
    float b = max(100.0f, -21.5f);
    assert(b == 100);

    char c = min('a', 'b');
    assert(c == 'a');
    return 0;
}
