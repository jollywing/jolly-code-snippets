#include <iostream>
using namespace std;

void main()
{
	char *p = new char[0];
	
	//用p读取p后面的内存没问题，但读出来的结果没有意义
	cout << "the address pointed by p is " << (void *)p << endl;
	cout << "p[0] is " <<p[0]<<endl;
	cout << "p[1] is " <<p[1] << endl;
	cout << "... ..." << endl;
	cout << "p[50] is " <<p[50] << endl;
	cout << "... ..." << endl;
	cout << "p[100] is " <<p[100] <<endl;
	//多于5103就不行了。
	cout << "p[5103] is " << p[5103] <<endl;
	
	//用p也可以写p后面的内存，但释放p时就会出问题
	//p[0] = 'a';
	//cout << "after assign, it is " <<p[0] <<endl;
	delete [] p;

	char *p1;
	//在分配之前，看看p1的值
	cout << "before new, p1 is "<<(void*)p1 << endl;
	p1 = new char[10];
	cout << "the address pointed by p1 is "<<(void *)p1 <<endl;
	cout << "p1[10] is " << p1[10] <<endl;
	//多于4991就不行了。
	cout << "p1[4991] is "<<p1[4991] <<endl;
	delete [] p1;

	//看看p1指向的内存被释放后，p1变成了什么值
	//结果表明并没有变成0
	cout << "after delete, p1 is " <<(void*)p1 << endl;
	
	return;
}

/*=====================结果分析===========================
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
  

分析：
00371C10偏移5104个字节的地址是00373000
00371C80偏移4992个字节的地址也是00373000
看来00373000之后是不能访问的空间，可能是别的进程的地址空间
那么可以得出结论：
------------------------------------------------------
通过一个有效的指针可以访问该指针后面进程允许访问的空间
不管后面的空间是否已经分配。
------------------------------------------------------

另外，可以看到指针指向的内存被释放后，指针并没清空
仍指向原来的地址，这是野指针。
=========================================================*/