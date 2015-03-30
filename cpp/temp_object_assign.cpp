#include <iostream>
using namespace std;

class C
{
public:
	C(int i)
	{
		c = i;
	}
	C()
	{
		c = 0;
		cout << "Default constructor called." << c << endl;
	}
	~C()
	{
		cout << "Destructor called." << c << endl;
	}
	void Print()
	{
		cout << c << endl;
	}
private:
	int c;
};

int main()
{
	C *p;
	p=new C[4];
	int n=1;
	for(int i=0;i<4;i++)
		p[i]=C(n++);
	for(int i=0;i<4;i++)
		p[i].Print();
    // 数组中的对象从后向前一一析构
	delete []p;
    return 0;
}

/* ---------- OUTPUT ---------
Default constructor called.0
Default constructor called.0
Default constructor called.0
Default constructor called.0
Destructor called.1
Destructor called.2
Destructor called.3
Destructor called.4
1
2
3
4
Destructor called.4
Destructor called.3
Destructor called.2
Destructor called.1
--------------------*/
