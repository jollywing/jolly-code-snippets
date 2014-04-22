
#include <iostream>
#include <exception>            // for use built-in exceptions

using std::cout;
using std::endl;
using std::exception;

// The buitin execptions inherited from exception
// - bad_alloc, thrown by `new'
// - dynamic_cast, thrown by `dynamic cast'
// - bad_typeid, thrown by `typeid'
// - bad_function_call, thrown by empty function object
// ...
// + logic_error
// + runtime_error
class MyException : public exception
{
    virtual const char * what() const throw() {
        return "My Exception happened!";
    }
};

void throwEmptyFuncCall()
{
    try {
        // emptyFunctionCall();
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}

void throwMyException()
{
    MyException myExp;
    try {
        throw myExp;
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
}

void throwAndCatch()
{
    try {
        throw 'D';
    }
    catch (char c) {
        cout << "catch a error char " << c << endl;
    }
    catch (...) {
        cout << "catch the default exception." << endl;
    }
}

int main(int argc, char *argv[])
{
    throwAndCatch();
    throwMyException();
    return 0;
}
