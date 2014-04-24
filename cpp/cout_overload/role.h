//********__role.h__******************
using namespace std;

class role
{
	friend ostream & operator<<(ostream &, const role &);

public:
	role(char *, int, int);


private:
	char name[16];
	int height;
	int age;
};

/*��ò�Ҫ�����ʵ��д��ͷ�ļ��У���Ϊ���ͷ�ļ���include��Σ�����ʵ�ֵĴ���Ҳ���������Ρ�*/
role::role(char * n, int h, int a)
{
	name = n;
	height = h;
	age =a;
}

ostream & operator<<(ostream &output, const role &r )
{
	output<<r.name<<endl;
	output<<"���"<<r.height<<endl;
	output<<"����"<<r.age<<endl;
    return output;
}
