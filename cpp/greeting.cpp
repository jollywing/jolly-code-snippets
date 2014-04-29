#include <iostream>
#include <string>

using namespace std;
/* A simple c++ program to examine `\\' */
int main()
{
    string name;
    cout << "Input your name: ";
    // cin will flush the cout buffer.

    // cin only can read a word, i.e., it will discards the leading whitespaces (space, tab, new-line)
    // and when it encounter another whitespace, it stops to put the char into cin buffer.
    cin >> name;

    const string greeting = "Hello, " + name + "!";
    const string greeting_line = "* " + greeting + " *";
    const string headline(greeting_line.size(), '*');
    const string second(greeting.size(), ' ');
    const string second_line = "* " + second + " *";

    cout << headline << endl;
    cout << second_line << endl;
    cout << greeting_line << endl;
    cout << second_line << endl;
    cout << headline << endl;

    cout << "And what's yours?";
    cin >> name;
    cout << "Hello, " + name + ", nice to meet you!" << endl;

    // ERROR: At least an operand need to be std::string
    // string ss = "hello " + ", the world!";
    {
        string ss = "hello";
        // + can concat a std::string and a 'char'.
        ss = ss + '!';
        ss = ss + "hello" + "dream!";
        {
            const string ss(10, '@');
            cout << ss << endl;
        }
        cout << ss << endl;
    }

    return 0;
}
