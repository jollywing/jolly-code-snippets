#include <iostream.h>
#include <stdio.h>
#include "student.h"

cStudent::cStudent(char * name, char * sex, int age, enum degree d):strSex(sex)/*�ó�Ա
��ʼ��ֵ��ʼ����Ա�ڲ�����*/
{
	SetStudent(name, age, d);
	
}

void cStudent::SetStudent(char * name, int age, enum degree d)
{
	strName = name;
	nAge = age;
	eDegree = d;
}

int cStudent::GetAge () const
{
	return nAge;
}

char * cStudent::GetName() const
{
	return strName;
}

enum degree cStudent::GetDegree() const
{
	return eDegree;
}

void cStudent::PrintStudent() const
{
	printf("������%s\n", strName);
	printf("�Ա�%s\n", strSex);
	printf("���䣺%d��\n", nAge);
	cout<<"ѧλ��"<<(enum degree)eDegree<<endl;
}
