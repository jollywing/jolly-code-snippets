#include "cSword.h"
#include "cHero.h"

void SetSword(cHero & hero, cSword & sword);

void main()
{
	cSword sword(2, 40);
	cHero hero("�����", 24, 3, 25);
	hero.PrintHero ();
	SetSword( hero, sword);
	hero.PrintHero ();
	hero.SetHero ("������", 80).PrintHero ();/*ͨ��thisָ�룬��Ա����������������*/
	return;
}

void SetSword(cHero & hero, cSword & sword)
{
	hero.sword = sword;
	return;
}