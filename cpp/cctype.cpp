#include <assert.h>
#include <cctype>
#include <iostream>

using namespace std;

void TestCharIdentify()
{
    assert(isspace(' '));
    assert(isalpha('X'));
    assert(isdigit('F') == false);

    // is alpha or digit
    assert(isalnum('1'));
    assert(ispunct('@'));
}

void TestCharUpperLower()
{
    char c = 65;
    if(isalpha(c)){
        if(isupper(c))
            c = tolower(c);
        else                    // islower
            c = toupper(c);
        int d = c;
        assert(c == 'a');
        cout << c << ":" << d << endl;
    }
}

int main()
{
    TestCharIdentify();
    TestCharUpperLower();
    return 0;
}
