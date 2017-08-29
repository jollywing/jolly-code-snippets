#ifndef _INHERIT_H_
#define _INHERIT_H_

#include <string.h>
#include <iostream>
using namespace std;

class CPeople
{
public:
	CPeople(const char * name)	//û���ṩĬ�ϵĹ��캯��
	{
		strcpy(m_name, name);
	}

	//����������Ͳ���const char *��
	//����char *���ᱨ��
	const char * get_name() const		//���ʺ���
	{	return m_name;	}

	//����Ϊvirtual�ĺ����Żᶯ̬��
	virtual void print() const
	{
		cout << "my name is " << m_name << endl;
	}

private:	//m_name��CHeroҲ�����صģ���Chero�Կ���ͨ��get_name���ʵ�
	char m_name[32];
};

class CHero : public CPeople
{
public:
	//��ΪCPeopleû��Ĭ�ϵĹ��캯����
	//������CHero�Ĺ��캯����
	//����ҪΪCpeople�Ĺ��캯���ṩchar *�Ĳ���
	//����ᱨ�������
	CHero( const char * name, int HP) : CPeople(name), m_HP(HP)
	{ }

	int get_hp() const
	{
		//����m_name��CPeople��˽�г�Ա, CHero���ʲ������ᱨ�������
		//strcpy(m_name, "mary");
		return m_HP;
	}

	//���ָ��Ǹ���ĳ�Ա����
	void print() const
	{
		CPeople::print();
		cout << "I'm a hero!" << endl;
	}

private:
	int m_HP;
};


#endif
