// g++ -std=c++11 TestLambda.cpp
#include <assert.h>
#include <string.h>
#include <cctype>
#include <iostream>

// template<typename T, typename Func>
// void ConvertArray(T array[], int size, Func func)
template<typename T>
void ConvertArray(T array[], int size)
{
    // need to tell g++ use c++11 standard,
    // otherwise auto will not have the feature of auto type derivation
    auto func = [&](){
        for(int i = 0; i < size; i++)
            array[i] = i;
    };
    func();
}

void TestLambdaWithoutOutside()
{
    char name[32] = "Hello, world!";
    auto upper_string = [](char *s){
        int size = strlen(s);
        for(int i=0; i < size; i++)
            s[i] = toupper(s[i]);
    };
    upper_string(name);
    std::cout << name << std::endl;
}

void TestLambda()
{
    int int_array[10] = {0};
    ConvertArray(int_array, 10);
    // ConvertArray<int>(int_array, 10, [&](){
    //             for(int i = 0; i < 10; i++){
    //                 int_array[i] = i;
    //             }
    //         });
    assert(int_array[9] == 9 && int_array[5] == 5);
}

int main()
{
    TestLambda();
    TestLambdaWithoutOutside();
    return 0;
}
