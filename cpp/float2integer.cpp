#include <windows.h>
#include <iostream>
using namespace std;

void translate(DWORD & a,float b)
{
	a=*(DWORD*)&b;
}

void main()
{
	DWORD a[10];
	float b[10];
	int i;
	
	cout <<"before convert, 10 numbers are:"<<endl;
	for(  i = 0; i<10; ++i){
		b[i] = i + 0.1;
		cout << b[i] << endl;
	}
	cout << endl;

	cout << "after convert, 10 numbers are:" <<endl;
	for ( i = 0; i< 10; ++i){
		translate(a[i],b[i]);
		cout << a[i] << endl;
	}

}

/************************result***************************************                                                              
before convert, 10 numbers are:
0.1
1.1
2.1
3.1
4.1
5.1
6.1
7.1
8.1
9.1

after convert, 10 numbers are:
1036831949
1066192077
1074161254
1078355558
1082340147
1084437299
1086534451
1088631603
1090623898
1091672474
************************************************************************/