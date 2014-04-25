#include "cSword.h"
#include "cHero.h"

void SetSword(cHero & hero, cSword & sword);

void main()
{
	cSword sword(2, 40);
	cHero hero("令狐冲", 24, 3, 25);
	hero.PrintHero ();
	SetSword( hero, sword);
	hero.PrintHero ();
	hero.SetHero ("风清扬", 80).PrintHero ();/*通过this指针，成员函数可以连续调用*/
	return;
}

void SetSword(cHero & hero, cSword & sword)
{
	hero.sword = sword;
	return;
}