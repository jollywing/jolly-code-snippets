
#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;

void TestStringConstruct()
{
    cout << "string str1(10, 'B') GET: ";
    string str1(10, 'B');
    cout << str1 << endl;

    cout << "string str2(\"Hello, the world!\"); GET: ";
    string str2("Hello, the world!");
    cout << str2 << endl;

    cout << "string str3(\"Hello, the world!\", 5); GET: ";
    string str3("Hello, the world!", 5);
    cout << str3 << endl;

    cout << "string str4(str2, 0, 5); GET: ";
    string str4(str2, 0, 5);
    cout << str4 << endl;
}

void TestStringIterate()
{
    string s = "CPPUNIT";
    assert(s.length() == s.size());

    cout << "List string: " << s << endl;
    // size() of length() 返回字符串对象的字符数
    // str2.at(i) == str2[i]
    for(int i = 0; i < s.size(); i++) {
        cout << i << " : " << s[i] << endl;
    }

    cout << "ITERATOR: ";
    string::iterator the_iterator;
    for(the_iterator = s.begin();
        the_iterator != s.end();
        the_iterator++)
        cout << *the_iterator << '\t';
    cout << endl;

    // rbegin() 返回一个逆向迭代器
    cout << "REVERSED ITERATOR: " << endl;
    string::reverse_iterator the_r_iterator;
    for(the_r_iterator = s.rbegin();
        the_r_iterator != s.rend();
        the_r_iterator++)
        cout << *the_r_iterator << '\t';
    cout << endl;
}

void TestStringCompare()
{
    // ==, >, <, >=, <=, !=
    string s("Hello");
    assert(s == "Hello");
    assert(s <= "Hillo");
}

void TestStringConcat()
{
    string s = "AA";
    string s2 = s + "BB";
    assert(s2 == "AABB");

    s += "CC";
    assert(s == "AACC");
}

void TestSubString()
{
    cout << "Test SubString ..." << endl;
    string a = "I'll Test substr method.";
    cout << a << endl;
    // Get substring from 5 to (5 + 4 - 1)
    string b = a.substr(5, 4);
    cout << b << endl;
    assert( b == "Test");
    cout << "Test SubString SUCCESS!" << endl;
}

int main(int argc, char *argv[]){


    // APPEND
    // basic_string &append( const basic_string &str );
    // basic_string &append( const char *str );
    // basic_string &append( const basic_string &str, size_type index, size_type len );
    // basic_string &append( const char *str, size_type num );
    // basic_string &append( size_type num, char ch );

    // ASSIGN
    // basic_string &assign( const basic_string &str );
    // basic_string &assign( const char *str );
    // basic_string &assign( const char *str, size_type num );
    // basic_string &assign( const basic_string &str, size_type index, size_type len );
    // basic_string &assign( size_type num, char ch );


    // return a const c string
    // const char *c_str();

    // cout << "The max size of str4 is " << str4.max_size() << endl;
    // cout << "The capacity of str4 is " << str4.capacity() << endl;

    // COMPARE: if this < str, return <0; if this == str, return 0; if this > str, return >0
    // int compare( const basic_string &str );
    // int compare( const char *str );
    // COMPARE THE OWN SUBSTR WITH STR
    // int compare( size_type index, size_type length, const basic_string &str );
    // COMPARE THE OWN SUBSTR WITH THE SUBSTR OF STR
    // int compare( size_type index, size_type length,
    //              const basic_string &str, size_type index2, size_type length2 );

    // COPY
    // copy <num> characters from <index> into <str>
    // return the number of chars copyed.
    // size_type copy( char *str, size_type num, size_type index );

    string str6;
    // bool empty()
    if(str6.empty()){
        cout << "new string is empty!" << endl;
    }
    else
        cout << "Why is new string not empty?" << endl;

    str6 = "How far to your school?";
    cout << str6 << endl;
    // basic_string &erase( size_type index = 0, size_type num = npos );
    str6.erase(10, 5);
    cout << str6 << endl;

    TestStringConstruct();
    TestStringIterate();
    TestStringCompare();
    TestStringConcat();
    // SUBSTR
    TestSubString();

    return 0;
}
