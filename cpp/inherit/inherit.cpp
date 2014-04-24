
#include "inherit.h"
//#include <iostream>
//using namespace std;

void main()
{
	CHero hero("john", 100 );
	cout << hero.get_name() << endl;
	cout << hero.get_hp() << endl;
	
	//测试多态
	CPeople people("mary");	

	//引用变量必须在声明时就初始化
	//并且不能修改引用变量去引用另一个变量
	CPeople & ref1 = people;
	ref1.print();
	//因为ref实际上是people，
	//所以下面的赋值语句实际上是peple=hero，
	//其实是调用了CPeople的赋值构造函数
	//复制构造函数是系统提供的。
	//ref = hero;
	//ref.print();

	CPeople & ref2 = hero;
	ref2.print();

	CPeople * ptr;
	ptr = &people;
	ptr->print();
	//并不会自动挂接，要进行指针类型的转换
	ptr = &hero;
	ptr->print();
	
	return;
}
