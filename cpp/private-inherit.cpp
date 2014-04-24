
#include <iostream>
using namespace std;

class Tool
{
public:
    Tool(int price):_price(price){
        cout << "aTool constructed." << endl;
    }
    virtual void Use(){}
    int Price(){return _price;}

    // To support 多态, deconstructor must be a virtual function.
    // otherwise, it won't call the deconstructor of subclass.
    virtual ~Tool(){cout << "aTool deconstructed." << endl;}
private:
    int _price;
};

// 私有继承：基类的公有成员和保护成员全部变为私有成员。
// private inheriting can not access the public function of base-class,
// even the constructor of base-class is also invisible.
// 私有继承: 不能 继承 接口，只能继承实现。
// B 私有继承于 A, 表示B在实现时能用到A的实现代码。
// B is not a A, but A has B.
class Knife: private Tool
{
public:
    Knife(int price, int length):Tool(price){
        _length = length;
        cout << "aKnife constructed." << endl;
    }
    virtual void Use(){cout << "Use Knife ..." << endl;}
    int Length(){return _length;}
    using Tool::Price; // use the interface of base class as public interface
    virtual ~Knife() {cout << "aKnife deconstructed." << endl;}
private:
    int _length;
};

int main(int argc, char *argv[])
{
    // private deprived class can not be converted to base calss object by client
    // Tool *tool = new Knife(15, 2);
    Knife *tool = new Knife(15, 2);
    tool->Use();
    delete tool;
    return 0;
}
