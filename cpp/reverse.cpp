#include <iostream.h>
#include <stdio.h>

void reverse();

void main()
{
	reverse();
	cout<<endl;
}

void reverse()
{
	char a;
	a = getchar();
	if (a == '\n')
		return;
	reverse();
	cout<<a;
}