#include <iostream.h>
#include <stdio.h>
#include "student.h"

cStudent::cStudent(char * name, char * sex, int age, enum degree d):strSex(sex)/*用成员
初始化值初始化成员内部常量*/
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
	printf("姓名：%s\n", strName);
	printf("性别：%s\n", strSex);
	printf("年龄：%d岁\n", nAge);
	cout<<"学位："<<(enum degree)eDegree<<endl;
}
