#include <stdio.h>
#include "cSword.h"

cSword::cSword(int l, int a)
{
	length = l;
	attack = a;
}

void cSword::discribe () const
{
	printf("佩剑长%d尺，配戴之后可增加%d点攻击力。\n\n", this->length, (*this).attack);
	/*this是对象的地址*/

}

cSword & cSword::SetSword (int l, int a)
{
	length = l;
	attack = a;
	return *this;
}