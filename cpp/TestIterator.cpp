#include <assert.h>
#include <iostream>
#include <iterator>
#include <cstring>
#include <vector>
#include <list>

void TestBackInserter()
{
    // vector, deque and list support back_inserter

    std::string s = "Dog";
    std::back_insert_iterator<std::string> it = back_inserter(s);
    // std::cout << *it << std::endl;

    std::string v = "Las";
    copy(v.begin(), v.end(), it);

    assert(s == "DogLas");
}

void TestInserter()
{
    std::string v = "Las";
    std::string s= "Dog";
    // insert elements before the given iterator
    copy(v.begin(), v.end(), inserter(s, s.begin()));
    assert(s == "LasDog");
    s = "Dog";
    copy(v.begin(), v.end(), inserter(s, s.end()));
    assert(s == "DogLas");
}

void TestFrontInserter()
{
    // list and deque support push_front, so they support front_inserter
    std::list<int> l;
    std::vector<int> v;
    for(int i = 0; i < 5; i ++){
        v.push_back(i);
        l.push_back(i + 10);
    }

    copy(v.begin(), v.end(), front_inserter(l));

    std::list<int>::const_iterator it;
    // 4 3 2 1 0 10 11 12 13 14
    for(it = l.begin(); it != l.end(); it ++)
        std::cout << *it << '\t';
    std::cout << std::endl;
}

int main()
{
    TestBackInserter();
    TestInserter();
    TestFrontInserter();
    return 0;
}
