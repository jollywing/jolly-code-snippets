/************************************************************************/
/* name: operatorOverload.cpp                                           */
/* desc: 练习操作符重载													*/
/* author:	jiqing Wu, 2007-10-18										*/
/************************************************************************/

#include <iostream>
#include <iomanip>	//due to setw(n)
using namespace std;
//-------------------interface----------------------------
class SecreteID
{
public:
	SecreteID(int first = 0, int middle = 0, int last = 0)
		: firstPart(first), middlePart(middle), lastPart(last)
	  {}
	ostream & print( ostream &) const;
	const SecreteID & operator=( SecreteID &rhs);
	SecreteID operator+( SecreteID &rhs);
	const SecreteID & operator+=( SecreteID &rhs);
	
private:
	int firstPart;
	int middlePart;
	int lastPart;
};

ostream & operator<<( ostream & out, SecreteID & id)
{
	return id.print( out );	
}

//----------------------implement-----------------------------

/* 后面的const修饰符表示是访问函数，
 * 如果声明中加了const，定义中也要加const。
 * 否则编译器将认为是不同的函数。*/
ostream & SecreteID::print(ostream & out) const
{
	out.setf(ios::right);
	out.fill('0');
	// note: setw只对紧跟在后面的输出有效
	out << setw(10) << firstPart <<'-'
		<< setw(10) << middlePart << '-' 
		<< setw(10) << lastPart << endl;
	
	return out;
}

//返回常量引用，考虑a=b=c，=右边的都是常量
const SecreteID & SecreteID::operator=( SecreteID & rhs )
{
	//防止自己给自己赋值
	//因为一般赋值之前会把目标对象清空
	//如果自己给自己赋值，则目标和源可能同时被清空
	if( this != &rhs)
	{
		firstPart = rhs.firstPart;
		middlePart = rhs.middlePart;
		lastPart = rhs.lastPart;
	}	
	return *this;
}

/* 不能返回引用，因为我们不允许(a+b) = c这样的表述*/
SecreteID SecreteID::operator+( SecreteID & rhs )
{
	firstPart += rhs.firstPart;
	middlePart += rhs.middlePart;
	lastPart += rhs.lastPart;
	return *this;
}

const SecreteID & SecreteID::operator+=( SecreteID &rhs)
{
	SecreteID lhs = *this;
	*this = lhs + rhs;
	return *this;
}


//---------------------------driver------------------
int main()
{
	SecreteID id1;
	SecreteID id2(22222, 33333, 11111);
	cout << "id 1 is: " << id1 <<endl;
	cout << "id 2 is: " << id2 <<endl;

	id1 = id2;
	cout << "after = , id 1 is: " << id1 <<endl;
	id1 += id2;
	cout << "after +=, id 1 is: " << id1 <<endl;

	/*	调用了默认的复制构造函数	
	 *	相当于 SecreteID id3(id1+id2) */
	SecreteID id3 = id1 + id2;
	cout << "id 3 is: " << id3 << endl;

	return 0;
	
}

/* --------------result ----------------------------
id 1 is: 0000000000-0000000000-0000000000

id 2 is: 0000022222-0000033333-0000011111
  
after = , id 1 is: 0000022222-0000033333-0000011111
	
after +=, id 1 is: 0000044444-0000066666-0000022222
	  
id 3 is: 0000066666-0000099999-0000033333
		
---------------------------------------------------*/
