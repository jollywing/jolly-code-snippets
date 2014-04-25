/************************************************************************/
/* name: operatorOverload.cpp                                           */
/* desc: ��ϰ����������													*/
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

/* �����const���η���ʾ�Ƿ��ʺ�����
 * ��������м���const��������ҲҪ��const��
 * �������������Ϊ�ǲ�ͬ�ĺ�����*/
ostream & SecreteID::print(ostream & out) const
{
	out.setf(ios::right);
	out.fill('0');
	// note: setwֻ�Խ����ں���������Ч
	out << setw(10) << firstPart <<'-'
		<< setw(10) << middlePart << '-' 
		<< setw(10) << lastPart << endl;
	
	return out;
}

//���س������ã�����a=b=c��=�ұߵĶ��ǳ���
const SecreteID & SecreteID::operator=( SecreteID & rhs )
{
	//��ֹ�Լ����Լ���ֵ
	//��Ϊһ�㸳ֵ֮ǰ���Ŀ��������
	//����Լ����Լ���ֵ����Ŀ���Դ����ͬʱ�����
	if( this != &rhs)
	{
		firstPart = rhs.firstPart;
		middlePart = rhs.middlePart;
		lastPart = rhs.lastPart;
	}	
	return *this;
}

/* ���ܷ������ã���Ϊ���ǲ�����(a+b) = c�����ı���*/
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

	/*	������Ĭ�ϵĸ��ƹ��캯��	
	 *	�൱�� SecreteID id3(id1+id2) */
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
