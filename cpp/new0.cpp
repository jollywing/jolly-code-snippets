#include <iostream>
using namespace std;

void main()
{
	char *p = new char[0];
	
	//��p��ȡp������ڴ�û���⣬���������Ľ��û������
	cout << "the address pointed by p is " << (void *)p << endl;
	cout << "p[0] is " <<p[0]<<endl;
	cout << "p[1] is " <<p[1] << endl;
	cout << "... ..." << endl;
	cout << "p[50] is " <<p[50] << endl;
	cout << "... ..." << endl;
	cout << "p[100] is " <<p[100] <<endl;
	//����5103�Ͳ����ˡ�
	cout << "p[5103] is " << p[5103] <<endl;
	
	//��pҲ����дp������ڴ棬���ͷ�pʱ�ͻ������
	//p[0] = 'a';
	//cout << "after assign, it is " <<p[0] <<endl;
	delete [] p;

	char *p1;
	//�ڷ���֮ǰ������p1��ֵ
	cout << "before new, p1 is "<<(void*)p1 << endl;
	p1 = new char[10];
	cout << "the address pointed by p1 is "<<(void *)p1 <<endl;
	cout << "p1[10] is " << p1[10] <<endl;
	//����4991�Ͳ����ˡ�
	cout << "p1[4991] is "<<p1[4991] <<endl;
	delete [] p1;

	//����p1ָ����ڴ汻�ͷź�p1�����ʲôֵ
	//���������û�б��0
	cout << "after delete, p1 is " <<(void*)p1 << endl;
	
	return;
}

/*=====================�������===========================
the address pointed by p is 00371C10
p[0] is
p[1] is
... ...
p[50] is 
... ...
p[100] is
p[5103] is 


the address pointed by p1 is 00371C10
p1[10] is
p1[4991] is 

before new, p1 is CCCCCCCC
after delete, p1 is 00371C10
  

������
00371C10ƫ��5104���ֽڵĵ�ַ��00373000
00371C80ƫ��4992���ֽڵĵ�ַҲ��00373000
����00373000֮���ǲ��ܷ��ʵĿռ䣬�����Ǳ�Ľ��̵ĵ�ַ�ռ�
��ô���Եó����ۣ�
------------------------------------------------------
ͨ��һ����Ч��ָ����Է��ʸ�ָ��������������ʵĿռ�
���ܺ���Ŀռ��Ƿ��Ѿ����䡣
------------------------------------------------------

���⣬���Կ���ָ��ָ����ڴ汻�ͷź�ָ�벢û���
��ָ��ԭ���ĵ�ַ������Ұָ�롣
=========================================================*/