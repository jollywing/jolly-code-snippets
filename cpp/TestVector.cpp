#include <iostream>
#include <vector>
#include <assert.h>

using std::cout; using std::endl;
using std::vector;

void TestVector(vector<char> &v)
{
    v.clear();
    assert(v.empty());

    v.push_back('a');
    v.push_back('b');
    vector<char>::size_type size = v.size();
    assert(size == 2);

    vector<char> temp;
    temp.push_back('c');
    temp.push_back('d');
    temp = v;
    assert(temp[0] == v[0]);

    // modifying to 'temp' won't change 'v'
    temp.erase(temp.begin());
    assert(temp.size() == 1);
    assert(v.size() == 2);
}

template<typename T>
void TestIterator(vector<T> &v)
{
    // need 'typename' before 'std::vector<T>::Iterator' because 'std::vector<T>' is a dependent scope
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); it++){
        cout << *it << '\t';
    }

    typename vector<T>::reverse_iterator rit;
    for(rit = v.rbegin(); rit != v.rend(); rit ++){
        cout << *rit << '\t';
    }

    it = v.begin();
    v.erase(it, it + 2);
    assert(v.size() == 0);
}

int main()
{
    vector<char> v;
    TestVector(v);
    TestIterator<char>(v);
    return 0;
}
