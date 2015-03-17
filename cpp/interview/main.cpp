
#include <iostream>
using namespace std;

class Cat
{
public:
    Cat(int age):itsAge(age)
    {
        HowManyCats ++;
    }
    virtual ~Cat() {HowManyCats--;}
    virtual int GetAge() {return itsAge;}
    virtual void SetAge(int age) {itsAge = age;}
    static int HowManyCats;
private:
    int itsAge;
};

// 注意，如果类里面声明了静态成员变量，必须在类外定义该变量。
int Cat::HowManyCats = 0;

int main()
{
    const int MaxCats = 5;
    int i;
    Cat *CatHouse[MaxCats];
    for(i = 0; i < MaxCats; i++) {
        CatHouse[i] = new Cat(i);
    }
    for(i = 0; i < MaxCats; i++) {
        cout << "There are ";
        cout << Cat::HowManyCats;
        cout << " cats left!\n";
        cout << "Deleting the one which is ";
        cout << CatHouse[i]->GetAge();
        cout << " years old\n";
        delete CatHouse[i];
        CatHouse[i] = 0;
    }
    return 0;
}
