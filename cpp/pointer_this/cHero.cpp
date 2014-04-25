#include "cHero.h"
#include <stdio.h>

cHero::cHero(char * n, int A, int l, int a):sword(l, a)/*对象成员的初始化*/
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
	printf("他叫%s,年纪大约%d。\n", name, age);
	sword.discribe ();
}