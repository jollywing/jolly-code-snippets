#include <stdio.h>
#include "cSword.h"

cSword::cSword(int l, int a)
{
	length = l;
	attack = a;
}

void cSword::discribe () const
{
	printf("�彣��%d�ߣ����֮�������%d�㹥������\n\n", this->length, (*this).attack);
	/*this�Ƕ���ĵ�ַ*/

}

cSword & cSword::SetSword (int l, int a)
{
	length = l;
	attack = a;
	return *this;
}