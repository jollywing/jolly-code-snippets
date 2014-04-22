#include <iostream>
using std::cout;
using std::endl;

template<typename T>
T MAX(T v1, T v2){
    return v1 > v2? v1 : v2;
}

template<typename T>
class A
{
    T v1;
    T v2;
public:
    void show_e1();

    template<typename U>
    void show_e2(U u);

    void show_all();
};

template<typename T>
void A<T>::show_e1()
{
    cout << v1 << endl;
}

// template<typename T, typename U>
// error: too many template parameters in template redeclaration

template<typename T>
template<typename U>
void A<T>::show_e2(U u)
{
    T t = v2 + 1;
    cout << u << ":" << t << endl;
}

template<typename T>
void A<T>::show_all()
{
    show_e1();
    show_e2(2);
}

int main(int argc, char *argv[])
{
    A<char> aa;
    aa.show_all();

    // compiler will regard T as int
    int i = MAX(2, 3);

    // give T explicityly, 2 will be regarded as float
    float f = MAX<float>(2, 6.0);
    cout<< i << "\t" << f << endl;
}
