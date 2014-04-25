#ifndef CHERO_H
#define CHERO_H

#include "cSword.h"

class cHero
{
	friend void SetSword (cHero &, cSword &);/*友员函数声明，可以访问对象的private成员*/

public:
	cHero(char* = "", int = 0, int = 0, int = 0);
	cHero & SetHero(char * n, int a);
	void PrintHero() const;

private:
	char * name;
	int age;
	cSword sword;/*把对象作为成员叫做复合*/
};

#endif