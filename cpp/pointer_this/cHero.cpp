#include "cHero.h"
#include <stdio.h>

cHero::cHero(char * n, int A, int l, int a):sword(l, a)/*�����Ա�ĳ�ʼ��*/
{
	name = n;
	age = A;
}

cHero & cHero::SetHero (char * n, int a)
{
	name = n;
	age = a;
	return *this;
}

void cHero::PrintHero () const
{
	printf("����%s,��ʹ�Լ%d��\n", name, age);
	sword.discribe ();
}