#ifndef CHERO_H
#define CHERO_H

#include "cSword.h"

class cHero
{
	friend void SetSword (cHero &, cSword &);/*��Ա�������������Է��ʶ����private��Ա*/

public:
	cHero(char* = "", int = 0, int = 0, int = 0);
	cHero & SetHero(char * n, int a);
	void PrintHero() const;

private:
	char * name;
	int age;
	cSword sword;/*�Ѷ�����Ϊ��Ա��������*/
};

#endif