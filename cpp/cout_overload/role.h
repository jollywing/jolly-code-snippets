//********__role.h__******************
#include <string.h>
#include <iostream>
using namespace std;

class role
{
	friend ostream & operator<<(ostream &, const role &);

public:
	role(const char *, int, int);


private:
	char name[16];
	int height;
	int age;
};

/*最好不要把类的实现写在头文件中，因为如果头文件被include多次，则类实现的代码也将被编译多次。*/
role::role(const char * n, int h, int a)
{
    strcpy(name, n);
	height = h;
	age =a;
}

ostream & operator<<(ostream &output, const role &r )
{
	output<<r.name<<endl;
	output<<"身高"<<r.height<<endl;
	output<<"年龄"<<r.age<<endl;
    return output;
}
