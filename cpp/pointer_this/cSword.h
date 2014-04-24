#ifndef CSWORD_H
#define CSWORD_H

class cSword
{
public:
	cSword(int = 0, int = 0);
	void discribe() const;
	cSword & SetSword(int l, int a);
private:
	int length;
	int attack;

};

#endif