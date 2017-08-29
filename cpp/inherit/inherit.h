#ifndef _INHERIT_H_
#define _INHERIT_H_

#include <string.h>
#include <iostream>
using namespace std;

class CPeople
{
public:
	CPeople(const char * name)	//没有提供默认的构造函数
	{
		strcpy(m_name, name);
	}

	//如果返回类型不是const char *，
	//而是char *，会报错
	const char * get_name() const		//访问函数
	{	return m_name;	}

	//声明为virtual的函数才会动态绑定
	virtual void print() const
	{
		cout << "my name is " << m_name << endl;
	}

private:	//m_name对CHero也是隐藏的，但Chero仍可以通过get_name访问到
	char m_name[32];
};

class CHero : public CPeople
{
public:
	//因为CPeople没有默认的构造函数，
	//所以在CHero的构造函数中
	//必须要为Cpeople的构造函数提供char *的参数
	//否则会报编译错误
	CHero( const char * name, int HP) : CPeople(name), m_HP(HP)
	{ }

	int get_hp() const
	{
		//由于m_name是CPeople的私有成员, CHero访问不到，会报编译错误
		//strcpy(m_name, "mary");
		return m_HP;
	}

	//部分覆盖父类的成员函数
	void print() const
	{
		CPeople::print();
		cout << "I'm a hero!" << endl;
	}

private:
	int m_HP;
};


#endif
